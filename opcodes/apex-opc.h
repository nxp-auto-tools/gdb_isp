/*
 * Copyrights
 */

#ifndef OPCODE_APEX_H
#define OPCODE_APEX_H

#define SHIFT_LEFT(v, p) ((v)<<(p)) //v - value; p - number of positions to shift
#define SHIFT_RIGHT(v, p) ((v)>>(p))

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
  unsigned long op_mask[5]; //operands positions
  unsigned int positions_to_shift[5];
  unsigned long non_read_pos; //positions of instr, that not reads by.

} apex_opc_info_t;

#endif // OPCODE_APEX_H
