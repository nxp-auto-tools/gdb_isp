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
	for(;table->name;table++)
		if ((data & ~table->op_pos & ~table->non_read_pos) == table->opcode)
			return table;
	return NULL;
}

int extract_operands (const apex_opc_info_t* operation,operand* operands,bfd_vma data){

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

	default:
		operands=NULL;
		return -1;
	}
	if (operands==NULL){
		return -1;
	}
	for (index=0; index<operation->num_of_operands;index++){
		operands[index].type = operation->op_type[index];
		operands[index].value = SHIFT_RIGHT((data & op_mask[index]), positions_to_shift[index]);
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

	bfd_vma mask1 = 0x8000;
	bfd_vma mask2 = 0x2000;
	bfd_vma mask3 = 0x6000;
	bfd_vma mask4 = 0x18000;

	/*fprintf(stderr,"cur_insn_addr before: 0x%08x\n",cur_insn_addr);
	bfd_vma insn_order_num = (cur_insn_addr & ~(mask1|mask2|mask3|mask4));
	fprintf(stderr,"insn_order_num: 0x%08x\n",insn_order_num);
	cur_insn_addr =	 (cur_insn_addr - insn_order_num) + insn_order_num*4;
	fprintf(stderr,"cur_insn_addr after: 0x%08x\n",cur_insn_addr);
*/
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
    	fprintf (stderr,"Wrong instruction type\n",NULL);
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
