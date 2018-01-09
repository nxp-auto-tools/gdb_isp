#ifndef _APEX_DIS_H_
#define _APEX_DIS_H_

const unsigned int bytes_per_word = 4;
const unsigned int bits_per_word = 32;
const unsigned int is_big_endian = 0;
const unsigned int single_word = 1;
const unsigned int double_word = 2;
const unsigned int mnemomic_string_len = 128;

typedef unsigned long long vliw_t;

enum instruction_type{
	scalar_instruction_type,
	vector_instruction_type,
	combined_instruction_type,
	scalar64_instruction_type,
	wrong_insruction_type
}instruction_type;

#endif // _APEX_DIS_H_
