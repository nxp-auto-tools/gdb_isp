#ifndef _APEX_DIS_H_
#define _APEX_DIS_H_

const unsigned int word_instruction_length = 4;
const unsigned int bits_per_word = word_instruction_length * 8;
const unsigned int pc_increment = 1;//one word
enum instruction_type{
	scalar_instruction_type,
	vector_instruction_type,
	combined_instruction_type,
	scalar64_instruction_type,
	wrong_insruction_type
}instruction_type;

#endif // _APEX_DIS_H_
