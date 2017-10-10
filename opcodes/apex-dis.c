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
#include "../gdb/common/errors.h"

typedef struct operand{
	bfd_vma value;
	operand_type type;
}operand;
extern const apex_opc_info_t const * const apex_APC_32b_scalar_opc_info;

int get_instruction_type (bfd_vma instruction_word);
apex_opc_info_t* finde_in_table (apex_opc_info_t* table, bfd_vma data);
unsigned int extract_operands (apex_opc_info_t* operation,operand* operands,bfd_vma data);
int compose_disasmed_string (apex_opc_info_t* instruction,operand* operands,char* string);

int get_instruction_type (bfd_vma instruction_word){ //read first two bit in instruction
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
		//warning("Wrong instruction type");
		return wrong_insruction_type;
	}
}
apex_opc_info_t* finde_in_table (apex_opc_info_t* table, bfd_vma data){ // brute force yet
	for(;table->name;table++)
		if ((data & ~table->op_pos & ~table->non_read_pos) == table->opcode)
			return table;
	return NULL;
}

unsigned int extract_operands (apex_opc_info_t* operation,operand* operands,bfd_vma data){

	int index;
	bfd_vma op_mask[5];
	unsigned char positions_to_shift[5];

	memset (op_mask, 0, 5*sizeof(bfd_vma));
	memset (positions_to_shift, 0, 5);

	switch(operation->op_pos){ // compare operands mask
	case first_scalar_operands_mask_type:
		switch(operation->num_of_operands){
		case 1:	/*OPERAND_LARGE_IMM*/
			op_mask[0]=OPERAND_LARGE_IMM;
			positions_to_shift[0]=0;
			break;
		case 2:	/*OPERAND_I1|OPERAND_I2*/
			op_mask[0]=OPERAND_I1;
			op_mask[1]=OPERAND_I2;
			positions_to_shift[0]=13;
			positions_to_shift[1]=0;
			break;
		case 3:/*OPERAND_FIRST|OPERAND_SECOND|OPERAND_C*/
			op_mask[0]=OPERAND_FIRST;
			op_mask[1]=OPERAND_SECOND;
			op_mask[2]=OPERAND_C;
			positions_to_shift[0]=20;
			positions_to_shift[1]=15;
			positions_to_shift[2]=0;
			break;
		}
		break;
	case second_scalar_operands_mask_type:
		/*OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD*/
		op_mask[0]=OPERAND_FIRST;
		op_mask[1]=OPERAND_SECOND;
		op_mask[2]=OPERAND_THIRD;
		positions_to_shift[0]=20;
		positions_to_shift[1]=15;
		positions_to_shift[2]=10;
		break;

	case third_scalar_operands_mask_type:
		/*SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM*/
		op_mask[0]=SHIFT_LEFT(OPERAND_SECOND,1);
		op_mask[1]=OPERAND_IMM;
		positions_to_shift[0]=16;
		positions_to_shift[1]=0;
		break;

	case fourth_scalar_operands_mask_type:
		/*OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH*/
		op_mask[0]=OPERAND_FIRST;
		op_mask[1]=OPERAND_SECOND;
		op_mask[2]=OPERAND_THIRD;
		op_mask[3]=OPERAND_FOURTH;
		positions_to_shift[0]=20;
		positions_to_shift[1]=15;
		positions_to_shift[2]=10;
		positions_to_shift[3]=5;
		break;

	case fifth_scalar_operands_mask_type:
		/*OPERAND_FIRST|OPERAND_IMM*/
		op_mask[0]=OPERAND_FIRST;
		op_mask[1]=OPERAND_IMM;
		positions_to_shift[0]=20;
		positions_to_shift[1]=0;
		break;

	case sixth_scalar_operands_mask_type:
		/*OPERAND_FIRST|OPERAND_SECOND*/
		op_mask[0]=OPERAND_FIRST;
		op_mask[1]=OPERAND_SECOND;
		positions_to_shift[0]=20;
		positions_to_shift[1]=15;
		break;

	case seventh_scalar_operands_mask_type:
		/*OPERAND_SECOND|OPERAND_THIRD*/
		op_mask[0]=OPERAND_SECOND;
		op_mask[1]=OPERAND_THIRD;
		positions_to_shift[0]=15;
		positions_to_shift[1]=10;
		break;

	case eighth_scalar_operands_mask_type:
		/*OPERAND_SECOND|OPERAND_THIRD_EXT_1*/
		op_mask[0]=OPERAND_SECOND;
		op_mask[1]=OPERAND_THIRD_EXT_1;
		positions_to_shift[0]=15;
		positions_to_shift[1]=9;
		break;

	//case ninth_scalar_operands_mask_type:

	case tenth_scalar_operands_mask_type:
		/*OPERAND_FIRST*/
		op_mask[0]=OPERAND_FIRST;
		positions_to_shift[0]=20;
		break;

	case eleventh_scalar_operands_mask_type:
		/*OPERAND_SECOND*/
		op_mask[0]=OPERAND_SECOND;
		positions_to_shift[0]=15;
		break;

	//case twelfth_scalar_operands_mask_type:

	case thirteenth_scalar_operands_mask_type:
		/*OPERAND_IMM*/
		op_mask[0]=OPERAND_IMM;
		positions_to_shift[0]=0;
		break;

	case no_operands:
		break;
	default:
		operands=NULL;
		return -1;
	}
	operands = malloc(sizeof(operand)*operation->num_of_operands);
	if (operands==NULL){
		return -1;
	}
	for (index=0; index<operation->num_of_operands;index++){
		operands[index].type = operation->op_type[index];
		operands[index].value = SHIFT_RIGHT((data & op_mask[index]), positions_to_shift[index]);
	}
	return 0;

}
int compose_disasmed_string (apex_opc_info_t* instruction,operand* operands, char* string){
	int index;
	strcat(string, instruction->name);
	for (index=0;index<instruction->num_of_operands;index++){
		switch(operands[index].type){
		case gap:
			strcat(string," _g_");
			break;
		case reg_t:
			strcat(string," r");
			break;
		case imm_t:
			strcat(string," #");
			break;
		}
	sprintf(string,"%ll",operands[index].value);
	}
	return strlen(string);
}
int
print_insn_apex(bfd_vma pc, disassemble_info *info){

	bfd_byte instr_low_bytes [word_instruction_length];
	bfd_byte instr_high_bytes [word_instruction_length];
	apex_opc_info_t* opcode_table;
	apex_opc_info_t* current_instruction;
	operand* operands; //dynamic!!! to free!
	char instr_string_shape[64];

    // read instruction-word at address pointed by "pc"
    int status = (*info->read_memory_func) (pc, instr_low_bytes,
    									word_instruction_length, info);
    if (status != 0)
    {
      (*info->memory_error_func) (status, pc, info);
      return -1;
    }

    // read next instruction-word at address pointed by "pc+1"
    /*status = (*info->read_memory_func) (pc+1, instr_low_bytes,
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
    	break;
    case combined_instruction_type:
    	break;
    case scalar64_instruction_type:
    	break;
    default:
    	error ("Wrong instruction type");
    	break;

    }
    current_instruction = finde_in_table(opcode_table,data);
    if (current_instruction == NULL){
    	error("can't find in table this instruction!\n");
    	return -1;
    }

    if(extract_operands(current_instruction,operands,data)<0){
    	error("Can't extract operands!\n");
    	return -1;
    }
    if(compose_disasmed_string(current_instruction,operands,instr_string_shape)<=0){
    	error("Error while composing string!\n");
    	return -1;
    }
    free(operands);
	return 0;
}
