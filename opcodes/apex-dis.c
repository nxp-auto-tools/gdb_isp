/*
 * Copyrights
 */
#include "sysdep.h"
#include <stdlib.h>
#include <stdio.h>
#include "dis-asm.h"
#include "apex-opc.h"
#include "apex-dis.h"
#include "elf-bfd.h"

typedef struct operand{
	long value;
	operand_type type;
}operand;

const char* vcs_str[] = {
		"push_l 0",
		"push_l 2",
		"nop",
		"fpop",
		"push_l 1",
		"push_l 3",
		"flip",
		"pop"
};
extern const apex_opc_info_t apex_APC_32b_scalar_opc_info[];
extern const apex_64_bit_opc_info_t apex_APC_64b_scalar_opc_info[];
extern const apex_opc_info_t apex_APC_32b_vector_opc_info[];

int get_instruction_type (bfd_vma instruction_word);
const apex_opc_info_t* finde_in_table (const apex_opc_info_t* table, bfd_vma insn_bits);
const apex_opc_info_t* finde_in_table_scalar_insn_part (const apex_opc_info_t* table, bfd_vma insn_bits);
const apex_opc_info_t* finde_in_table_vector_insn_part (const apex_opc_info_t* table, bfd_vma insn_bits);
const apex_64_bit_opc_info_t* finde_in_vliw_table (const apex_64_bit_opc_info_t* table, vliw_t insn_bits);
int extract_operands (const apex_opc_info_t* operation,operand* operands,bfd_vma insn_bits);
int extract_vliw_operands (const apex_64_bit_opc_info_t* operation,operand* operands,vliw_t insn_bits);
int compose_scalar_mnemonic (const apex_opc_info_t* instruction,operand* operands,char* string);
int compose_64b_scalar_mnemonic (const apex_64_bit_opc_info_t* instruction,operand* operands,char* string);
int compose_vector_mnemonic (const apex_opc_info_t* instruction,operand* operands,char* string);
int (*compose_mnemonic) (const apex_opc_info_t* instruction,operand* operands,char* string);

int get_instruction_type (bfd_vma instruction_word){ //read first two bit in instruction
	instruction_word &=0xc0000000;
	instruction_word >>= 30;
	switch (instruction_word){
	case 0:
		return scalar_instruction_type;
	case 1:
		return vector_instruction_type;
	case 2:
		return combined_instruction_type;
	case 3:
		return scalar64_instruction_type;
	default:
		return wrong_insruction_type;
	}
}
const apex_opc_info_t* finde_in_table (const apex_opc_info_t* table, bfd_vma insn_bits){ // brute force yet
	bfd_vma op_pos;//operand position
	unsigned int ind;
	for(;table->name;table++){
		for (ind=0,op_pos=0;ind<table->num_of_operands;ind++)
			op_pos|=SHIFT_LEFT(table->op_mask[ind],table->op_offset[ind]);
		op_pos|=table->non_read_pos;
		if ((insn_bits & ~op_pos) == table->opcode)
			return table;
	}
	return NULL;
}
const apex_opc_info_t* finde_in_table_scalar_insn_part (const apex_opc_info_t* table, bfd_vma insn_bits){ // brute force yet
	bfd_vma op_pos;//operand position
	unsigned int ind;
	for(;table->name;table++){
		for (ind=0,op_pos=0;ind<table->num_of_operands;ind++)
			op_pos|=SHIFT_LEFT(table->op_mask[ind],table->op_offset[ind]);
		op_pos|=table->non_read_pos;
		if (((insn_bits) & ~op_pos) == (table->opcode | 0x80000000))
			return table;
	}
	return NULL;
}
const apex_opc_info_t* finde_in_table_vector_insn_part (const apex_opc_info_t* table, bfd_vma insn_bits){ // brute force yet
	bfd_vma op_pos;//operand position
	unsigned int ind;
	for(;table->name;table++){
		for (ind=0,op_pos=0;ind<table->num_of_operands;ind++)
			op_pos|=SHIFT_LEFT(table->op_mask[ind],table->op_offset[ind]);
		op_pos|=table->non_read_pos;
		if (((insn_bits & 0x3FFFFFFF) & ~op_pos) == (table->opcode & 0x3FFFFFFF))
			return table;
	}
	return NULL;
}
const apex_64_bit_opc_info_t* finde_in_vliw_table (const apex_64_bit_opc_info_t* table, vliw_t insn_bits){ // brute force yet
	vliw_t op_pos;//operand position
	unsigned int ind;
	for(;table->name;table++){
		for (ind=0,op_pos=0;ind<table->num_of_operands;ind++)
			op_pos|=SHIFT_LEFT(table->op_mask[ind],table->op_offset[ind]);
		op_pos|=table->non_read_pos;
		if ((insn_bits & ~op_pos) == table->opcode)
			return table;
	}
	return NULL;
}

int extract_operands (const apex_opc_info_t* operation,operand* operands,bfd_vma insn_bits){

	unsigned int index;
	for (index=0; index<operation->num_of_operands;index++){
		operands[index].type = operation->op_type[index];
		operands[index].value = SHIFT_RIGHT(insn_bits, operation->op_offset[index]) & operation->op_mask[index];
	}
	return index;
}
int extract_vliw_operands (const apex_64_bit_opc_info_t* operation,operand* operands,vliw_t insn_bits){

	unsigned int index;
	for (index=0; index<operation->num_of_operands;index++){
		operands[index].type = operation->op_type[index];
		operands[index].value = SHIFT_RIGHT(insn_bits, operation->op_offset[index]) & operation->op_mask[index];
	}
	return index;
}

int compose_scalar_mnemonic (const apex_opc_info_t* instruction,operand* operands, char* string){
	unsigned int index;
	char value_string [8];
	memset (value_string,0,8);
	strcat(string, instruction->name);
	for (index=0;index<instruction->num_of_operands;index++){
		switch(operands[index].type){
		case gap:
			strcat(string," _g_");
			break;
		case reg_t:
			strcat(string," r");
			sprintf(value_string,"%ld",operands[index].value);
			break;
		case imm_t:
			strcat(string," #");
			sprintf(value_string,"%ld",operands[index].value);
			break;
		default:
	        fprintf (stderr,"_compose_scalar_mnemonic: wrong operand type\n");
	        break;

		}
	strcat(string,value_string);
	}
	return strlen(string);
}
int compose_64b_scalar_mnemonic (const apex_64_bit_opc_info_t* instruction,operand* operands, char* string){
	unsigned int index;
	char value_string [8];
	memset (value_string,0,8);
	strcat(string, instruction->name);
	for (index=0;index<instruction->num_of_operands;index++){
		switch(operands[index].type){
		case gap:
			strcat(string," _g_");
			break;
		case reg_t:
			strcat(string," r");
			sprintf(value_string,"%ld",operands[index].value);
			break;
		case imm_t:
			strcat(string," #");
			sprintf(value_string,"%ld",operands[index].value);
			break;
		default:
	        fprintf (stderr,"_compose_scalar_mnemonic: wrong operand type\n");
	        break;

		}
	strcat(string,value_string);
	}
	return strlen(string);
}

int compose_vector_mnemonic (const apex_opc_info_t* instruction,operand* operands, char* string){
	unsigned int index;
	long imm;
	char value_string [8];
	memset (value_string,0,8);
	strcat(string, instruction->name);
	for (index=0;index<instruction->num_of_operands;index++){
		switch(operands[index].type){
		case gap:
			strcat(string," _g_");
			break;
		case reg_t:
			strcat(string," r");
			sprintf(value_string,"%ld",operands[index].value);
			break;
		case imm_t:
			imm = operands[index].value;
			if(index<instruction->num_of_operands-1)
				if(operands[index+1].type==imm_t)
					imm=(SHIFT_LEFT(operands[index].value,instruction->op_offset[index])|operands[index+1].value);
			strcat(string," #");
			sprintf(value_string,"%ld",imm);
			break;
		case vcs_t:
			strcat(string," vcs");
			sprintf(value_string,"%s", vcs_str[operands[index].value]);
			break;
		case f_t:
			strcat(string," flag=");
			if (operands[index].value > 0)
				sprintf(value_string,"true");
			else
				sprintf(value_string,"false");
			break;
		case sel_t:
			strcat(string," sel");
			sprintf(value_string,"%ld",operands[index].value);
			break;
		}
	strcat(string,value_string);
	}
	return strlen(string);
}

int
print_insn_apex(bfd_vma cur_insn_addr, disassemble_info *info){

	bfd_vma next_insn_addr = cur_insn_addr + bytes_per_word;
	bfd_vma high_bits,low_bits;
	bfd_byte instr_low_bytes [bytes_per_word];
	bfd_byte instr_high_bytes [bytes_per_word];
	const apex_opc_info_t *opcode_table;
	const apex_opc_info_t *current_instruction,*scalar_insn_part,*vector_insn_part;
	operand operands[6];
	char insns_mnemonic[mnemomic_string_len];

	memset(insns_mnemonic,0,mnemomic_string_len);
	memset(operands,0,5*sizeof(operands[0]));

    // read instruction-word at address pointed by "pc"
	int status = (*info->read_memory_func) (cur_insn_addr, instr_high_bytes,
    									bytes_per_word, info);

    if (status != 0){
      (*info->memory_error_func) (status, cur_insn_addr, info);
      fprintf (stderr,"memory read func worked in wrong way\n");
      return -1;
    }

    high_bits = bfd_get_bits (instr_high_bytes, bits_per_word, is_big_endian);

    switch (get_instruction_type(high_bits)){

    case scalar_instruction_type:
    	compose_mnemonic = compose_scalar_mnemonic;
    	opcode_table = apex_APC_32b_scalar_opc_info;
    	break;
    case vector_instruction_type:
    	compose_mnemonic = compose_vector_mnemonic;
    	opcode_table = apex_APC_32b_vector_opc_info;
    	break;

    case combined_instruction_type:
        // read next instruction-word at address pointed by "pc+1" (for 64-bit insns)
        status = (*info->read_memory_func) (next_insn_addr, instr_low_bytes,
        		bytes_per_word, info);
        if (status != 0)
        {
          (*info->memory_error_func) (status, next_insn_addr, info);
          return -1;
        }
        low_bits = bfd_get_bits (instr_low_bytes, bits_per_word, is_big_endian);

    	opcode_table = apex_APC_32b_scalar_opc_info;
    	scalar_insn_part = finde_in_table_scalar_insn_part(opcode_table,high_bits);
     	opcode_table = apex_APC_32b_vector_opc_info;
    	vector_insn_part = finde_in_table_vector_insn_part(opcode_table,low_bits);
        info->fprintf_func(info->stream, "_vliw ");

    	compose_mnemonic = compose_scalar_mnemonic;
        if (scalar_insn_part != NULL){
        	extract_operands(scalar_insn_part,operands,high_bits);
        	if(compose_mnemonic(scalar_insn_part,operands,insns_mnemonic)>0){
    			strcat(insns_mnemonic," ");
        		compose_mnemonic = compose_vector_mnemonic;
        		if (vector_insn_part != NULL){
        			extract_operands(vector_insn_part,operands,high_bits);
        			if(compose_mnemonic(vector_insn_part,operands,insns_mnemonic)>0){
        				info->fprintf_func(info->stream, " %s", insns_mnemonic);
        				return double_word;
        			}
        		}
        	}
        }

        fprintf (stderr,"_print_insn_combined_: unparsed command with addr=0x%08lx\n",cur_insn_addr);
        info->fprintf_func(info->stream, "0x%08lx ",high_bits);
        info->fprintf_func(info->stream, "0x%08lx ",low_bits);
		return double_word;

    case scalar64_instruction_type:
        // read next instruction-word at address pointed by "pc+1" (for 64-bit insns)
        status = (*info->read_memory_func) (next_insn_addr, instr_low_bytes,
        		bytes_per_word, info);
        if (status != 0)
        {
          (*info->memory_error_func) (status, next_insn_addr, info);
          return -1;
        }
        low_bits = bfd_get_bits (instr_low_bytes, bits_per_word, is_big_endian);

        //composing vliw_command
        vliw_t vliw_insn_value = high_bits;
        vliw_insn_value<<=bits_per_word;
        vliw_insn_value|=low_bits;

        const apex_64_bit_opc_info_t *vliw_opcode_table=apex_APC_64b_scalar_opc_info;

    	const apex_64_bit_opc_info_t *vliw_insn_entity = finde_in_vliw_table(vliw_opcode_table,vliw_insn_value);
        info->fprintf_func(info->stream, "_vliw ");

        if (vliw_insn_entity != NULL){
        	extract_vliw_operands(vliw_insn_entity,operands,vliw_insn_value);
        	if(compose_64b_scalar_mnemonic(vliw_insn_entity,operands,insns_mnemonic)>0){
        		info->fprintf_func(info->stream, "%s",insns_mnemonic);
        		return double_word;
        	}
        }
        fprintf (stderr,"_print_insn_scalar_64b_: unparsed command with addr=0x%08lx\n",cur_insn_addr);
        info->fprintf_func(info->stream, "0x%08lx ",high_bits);
        info->fprintf_func(info->stream, "0x%08lx ",low_bits);
		return double_word;

    default:
    	fprintf (stderr,"_print_insn: unrecognized insn type\n");
        info->fprintf_func(info->stream, "0x%08lx",high_bits);
    	return single_word;
    }


    current_instruction = finde_in_table(opcode_table,high_bits);

    if (current_instruction != NULL){
    	extract_operands(current_instruction,operands,high_bits);
    	if(compose_mnemonic(current_instruction,operands,insns_mnemonic)>0){
    		info->fprintf_func(info->stream,"%s", insns_mnemonic);
    		return single_word;
    	}
    }

    fprintf (stderr,"_print_insn: unparsed command with addr=0x%08lx\n",cur_insn_addr);
    info->fprintf_func(info->stream, "0x%08lx",high_bits);
	return single_word;
}
