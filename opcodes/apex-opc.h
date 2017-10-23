/*
 * Copyrights
 */

#ifndef OPCODE_APEX_H
#define OPCODE_APEX_H

#define SHIFT_LEFT(v, p) ((v)<<(p)) //v - value; p - number of positions to shift
#define SHIFT_RIGHT(v, p) ((v)>>(p))

#define NONE_OPERAND 0x00000000U

#define OPERAND_FIRST			0x01F00000U //[20:24] bits
#define OPERAND_SECOND			0x000F8000U //[15:19] bits
#define OPERAND_THIRD			0x00007C00U //[10:14] bits
#define OPERAND_THIRD_EXT_1		0x00007E00U // [9:14] bits
#define OPERAND_FOURTH			0x000003E0U //  [5:9] bits
#define OPERAND_C				0x00007FFFU // [0:14] bits
#define OPERAND_IMM				0x0000FFFFU // [0:15] bits
#define OPERAND_LARGE_IMM		0x01FFFFFFU // [0:24] bits
#define OPERAND_I1				0x01FFE000U //[13:24] bits
#define OPERAND_I2				0x00001FFFU	// [0:12] bits

#define OPERAND_s0				0x00000C00U //[10:11] bits
#define OPERAND_i0				0x01C00000U //[22:24] bits
#define OPERAND_i0_shftd_right	0x00380000U //[19:21] bits
#define OPERAND_d0				0x01800000U //[22:23] bits

typedef enum operand_type{
	gap,
	reg_t,
	imm_t,

}operand_type;

typedef struct apex_opc_info_t
{
  const char *name;
  unsigned long opcode;
  unsigned int num_of_operands;
  operand_type op_type[5];
  unsigned long op_pos[5]; //operands positions
  unsigned int positions_to_shift[5];
  unsigned long non_read_pos; //positions of instr, that not reads by.

} apex_opc_info_t;

#endif // OPCODE_APEX_H
