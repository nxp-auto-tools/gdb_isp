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
	bfd_vma value;
	operand_type type;
}operand;
extern const apex_opc_info_t apex_APC_32b_scalar_opc_info[135];

int get_instruction_type (bfd_vma instruction_word);
const apex_opc_info_t* finde_in_table (const apex_opc_info_t* table, bfd_vma data);
int extract_operands (const apex_opc_info_t* operation,operand* operands,bfd_vma data);
int compose_mnemonic (const apex_opc_info_t* instruction,operand* operands,char* string);

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
const apex_opc_info_t* finde_in_table (const apex_opc_info_t* table, bfd_vma data){ // brute force yet
	bfd_vma op_pos;
	unsigned int ind;
	for(;table->name;table++){
		for (ind=0;ind<table->num_of_operands;ind++)
			op_pos|=table->op_pos[ind];
		op_pos|=table->non_read_pos;
		if ((data & ~op_pos) == table->opcode)
			return table;
	}
	return NULL;
}

int extract_operands (const apex_opc_info_t* operation,operand* operands,bfd_vma data){

	int index;
	for (index=0; index<operation->num_of_operands;index++){
		operands[index].type = operation->op_type[index];
		operands[index].value = SHIFT_RIGHT((data & operation->op_pos[index]), operation->positions_to_shift[index]);
	}
	return 0;
}

int compose_mnemonic (const apex_opc_info_t* instruction,operand* operands, char* string){
	int index;
	const char* value_string [8];
	memset (value_string,0,8);
	strcat(string, instruction->name);
	for (index=0;index<instruction->num_of_operands;index++){
		switch(operands[index].type){
		case gap:
			strcat(string," _g_");
			break;
		case reg_t:
			strcat(string," r");
			sprintf(value_string,"%d",operands[index].value);
			break;
		case imm_t:
			strcat(string," #");
			sprintf(value_string,"0x%08x",operands[index].value);
			break;
		}
	strcat(string,value_string);
	}
	return strlen(string);
}

int
print_insn_apex(bfd_vma cur_insn_addr, disassemble_info *info){

	bfd_byte instr_low_bytes [word_instruction_length];
	// bfd_byte instr_high_bytes [word_instruction_length];
	const apex_opc_info_t* opcode_table;
	const apex_opc_info_t* current_instruction;
	operand operands[5];
	char instr_string_shape[64];

	memset(instr_string_shape,0,64);
	memset(operands,0,5*sizeof(operands[0]));

    // read instruction-word at address pointed by "pc"
	int status = (*info->read_memory_func) (cur_insn_addr, instr_low_bytes,
    									word_instruction_length, info);

    if (status != 0){
      (*info->memory_error_func) (status, cur_insn_addr, info);
      fprintf (stderr,"memory read func worked in wrong way\n");
      return -1;
    }
    // read next instruction-word at address pointed by "pc+1" (for 64-bit insns)
    /*status = (*info->read_memory_func) (pc+word_instruction_length, instr_low_bytes,
    									word_instruction_length, info);
    if (status != 0)
    {
      (*info->memory_error_func) (status, pc, info);
      return -1;
    }*/

    bfd_vma data = bfd_get_bits (instr_low_bytes, word_instruction_length * 8, info->display_endian == BFD_ENDIAN_LITTLE);

    switch (get_instruction_type(data)){

    case scalar_instruction_type:
    	opcode_table = apex_APC_32b_scalar_opc_info;
    	break;
    case vector_instruction_type:
   // 	break;
    case combined_instruction_type:
  //  	break;
    case scalar64_instruction_type:
   // 	break;
    default:
    	//fprintf (stderr,"Wrong instruction type\n",NULL);
    	break;
    }

    current_instruction = finde_in_table(opcode_table,data);

    if (current_instruction == NULL){
        info->fprintf_func(info->stream, "0x%08x",data);
    	return word_instruction_length;
    }
    if(extract_operands(current_instruction,operands,data)<0){
    	//fprintf (stderr,"\tNext instruction have no operands:\n",NULL);
    }
    if (operands==NULL){
    	//fprintf (stderr,"For some reason operands are empty\n",NULL);
    }else
		if(compose_mnemonic(current_instruction,operands,instr_string_shape)<=0){
	    	fprintf (stderr,"Error while composing string!\n",NULL);
		}
    info->fprintf_func(info->stream, instr_string_shape);
	return word_instruction_length;
}
