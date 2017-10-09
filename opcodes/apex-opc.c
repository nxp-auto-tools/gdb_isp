/*
 * Copyrights
 */


//#include "sysdep.h"
#include "apex-opc.h"

const apex_opc_info_t apex_APC_32b_scalar_opc_info[] =
{
		/*Load and Store instructions*/
	{        "lb", 0x18000000U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_C, 0},
	{       "lbu", 0x1A000000U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_C, 0},
	{  		 "lh", 0x1C000000U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_C, 0},
	{       "lhu", 0x20000000U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_C, 0},
	{        "lw", 0x22000000U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_C, 0},
	{      	 "sb", 0x26000000U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_C, 0},
	{        "sh", 0x28000000U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_C, 0},
	{        "sw", 0x2A000000U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_C, 0},
	{    "lbpost", 0x00000022U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{	"lbupost", 0x00000023U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{  	 "lhpost", 0x00000024U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{  	"lhupost", 0x00000025U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{    	"lhi", 0x1E000000U, 2, {reg_t,imm_t,gap,gap,gap}, OPERAND_FIRST|OPERAND_IMM, 0xF0000},
	{    "lwpost", 0x00000026U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{    "sbpost", 0x00000027U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{    "shpost", 0x00000028U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{    "swpost", 0x00000029U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
			/*ACP Integer instructions*/
	{		"add", 0x00000003U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "addx", 0x00000004U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{	   "addi", 0x04000000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{     "addix", 0x04200000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{     "addui", 0x06000000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{    "adduix", 0x06200000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{     	"sub", 0x0000001BU, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "subx", 0x0000001CU, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "subi", 0x04400000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{     "subix", 0x04600000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{     "subui", 0x06400000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{    "subuix", 0x06600000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{       "sll", 0x00000015U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "slli", 0x0000001FU, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "ssll", 0x00000031U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{     "sslli", 0x00000034U, 2, {reg_t,imm_t,gap,gap,gap}, OPERAND_SECOND|OPERAND_THIRD_EXT_1, 0x100},
	{ 	   "ssla", 0x00000032U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{     "sslai", 0x00000035U, 2, {reg_t,imm_t,gap,gap,gap}, OPERAND_SECOND|OPERAND_THIRD_EXT_1, 0x100},
	{       "sra", 0x00000019U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "srai", 0x00000020U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{       "srl", 0x0000001AU, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "srli", 0x00000021U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{        "rl", 0x00000033U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{       "rli", 0x00000036U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "srlo", 0x00000042U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{   "add_sll", 0x02000001U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "add_sra", 0x02000002U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "add_srl", 0x02000003U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{  "addx_sll", 0x02000005U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{  "addx_sra", 0x02000006U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{  "addx_srl", 0x02000007U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "sub_sll", 0x02000009U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "sub_sra", 0x0200000AU, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "sub_srl", 0x0200000BU, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{  "subx_sll", 0x0200000DU, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{  "subx_sra", 0x0200000EU, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{  "subx_srl", 0x0200000FU, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "and_sll", 0x02000011U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "and_sra", 0x02000012U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "and_srl", 0x02000013U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{    "or_sll", 0x02000015U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{    "or_sra", 0x02000016U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{    "or_srl", 0x02000017U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "xor_sll", 0x02000019U, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "xor_sra", 0x0200001AU, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "xor_srl", 0x0200001BU, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "xtd_sll", 0x0200001DU, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "xtd_sra", 0x0200001EU, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   "xtd_srl", 0x0200001FU, 4, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH,0},
	{   	"xtd", 0x0000001EU, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "xtdi", 0x07600000U, 2, {reg_t,imm_t,gap, gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{    "hadduu", 0x00000038U, 3, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{    "haddss", 0x00000039U, 3, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{   "rhadduu", 0x0000003AU, 3, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{   "rhaddss", 0x0000003BU, 3, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{  "abs_diff", 0x0000003CU, 3, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{ "abs_diffu", 0x0000003DU, 3, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{   "add_sat", 0x0000003EU, 3, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{  "add_satu", 0x0000003FU, 3, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{   "sub_sat", 0x00000040U, 3, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{  "sub_satu", 0x00000041U, 3, {reg_t,reg_t,reg_t,imm_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{       "clb", 0x00000007U, 2, {reg_t,reg_t,gap,gap,gap}, OPERAND_FIRST|OPERAND_SECOND, 0x7F00},
	{       "clz", 0x0000002FU, 2, {reg_t,reg_t,gap,gap,gap}, OPERAND_FIRST|OPERAND_SECOND, 0x7F00},
	{      "pcnt", 0x00000030U, 2, {reg_t,reg_t,gap,gap,gap}, OPERAND_FIRST|OPERAND_SECOND, 0x7F00},
	{       "abs", 0x00000037U, 2, {reg_t,reg_t,gap,gap,gap}, OPERAND_FIRST|OPERAND_SECOND, 0x7F00},
	{       "sel", 0x34000000U, 4, {reg_t,reg_t,reg_t,reg_t,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD|OPERAND_FOURTH, 0x1F},
	{  "mulss_lo", 0x00000044U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x200},
	{  "mulss_hi", 0x00000144U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x200},
	{  "mulsu_lo", 0x00000045U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x200},
	{  "mulsu_hi", 0x00000145U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x200},
	{  "muluu_lo", 0x00000046U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x200},
	{  "muluu_hi", 0x00000146U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x200},
	{    "lmulss", 0x00000009U, 2, {reg_t,reg_t,gap,gap,gap}, OPERAND_SECOND|OPERAND_THIRD, 0x1F00300},
	{    "lmulsu", 0x0000000AU, 2, {reg_t,reg_t,gap,gap,gap}, OPERAND_SECOND|OPERAND_THIRD, 0x1F00300},
	{    "lmuluu", 0x0000000BU, 2, {reg_t,reg_t,gap,gap,gap}, OPERAND_SECOND|OPERAND_THIRD, 0x1F00300},
		/*ACP Logical instructions*/
	{       "and", 0x00000005U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "andi", 0x06800000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{      "andi", 0x2C000000U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_C,0},
	{        "or", 0x0000000DU, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{       "ori", 0x06A00000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{       "ori", 0x27000000U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_C,0},
	{       "xor", 0x0000001DU, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "xori", 0x06C00000U, 2, {reg_t,reg_t,imm_t,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{      "xori", 0x30000000U, 3, {reg_t,reg_t,imm_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_C,0},
	{       "neg", 0x00000006U, 2, {reg_t,reg_t,gap,gap,gap}, OPERAND_FIRST|OPERAND_SECOND, 0x7F00},
		/*ACP Comparision instructions*/
	{       "seq", 0x0000000EU, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "seqi", 0x04800000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{       "sne", 0x00000018U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "snei", 0x05200000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{       "sge", 0x0000000FU, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "sgei", 0x04A00000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{      "sgeu", 0x00000010U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{     "sgeui", 0x06E00000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{       "sgt", 0x00000011U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "sgti", 0x04C00000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{      "sgtu", 0x00000012U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{     "sgtui", 0x07000000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{       "sle", 0x00000013U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "slei", 0x04E00000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{      "sleu", 0x00000014U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{     "sleui", 0x07000000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{       "slt", 0x00000016U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{      "slti", 0x05000000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{      "sltu", 0x00000017U, 3, {reg_t,reg_t,reg_t,gap,gap}, OPERAND_FIRST|OPERAND_SECOND|OPERAND_THIRD, 0x300},
	{     "sltui", 0x07400000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
				/*Control instructions*/
	{      "beqz", 0x08000000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{      "bnez", 0x0A000000U, 2, {reg_t,imm_t,gap,gap,gap}, SHIFT_LEFT(OPERAND_SECOND,1)|OPERAND_IMM,0},
	{         "j", 0x10000000U, 1, {imm_t,gap,gap,gap,gap}, OPERAND_LARGE_IMM,0},
	{        "jr", 0x16000000U, 1, {reg_t,gap,gap,gap,gap}, OPERAND_FIRST,0xFFFFF},
	{       "jal", 0x12000000U, 1, {imm_t,gap,gap,gap,gap}, OPERAND_LARGE_IMM,0},
	{      "jalr", 0x16000000U, 1, {reg_t,gap,gap,gap,gap}, OPERAND_FIRST,0xFFFFF},
	{        "do", 0x0C000000U, 2, {reg_t,imm_t,gap,gap,gap}, OPERAND_FIRST|OPERAND_IMM,0xF0000},
	{       "doi", 0x0E000000U, 2, {imm_t,imm_t,gap,gap,gap}, OPERAND_I1|OPERAND_I2,0},
	{     "swbrk", 0x00000001U, 0, {gap,gap,gap,gap,gap}, NONE_OPERAND,0},
	{       "nop", 0x00000000U, 0, {gap,gap,gap,gap,gap}, NONE_OPERAND,0},
	{      "Wait", 0x32000000U, 1, {imm_t,gap,gap,gap,gap}, OPERAND_IMM,0x1FF0000},
	{       	/*On-Chip debugger Instructions*/
			 "mv", 0x0000002EU, 1, {reg_t,gap,gap,gap,gap}, OPERAND_SECOND,0x1F07F00},
	{     "sltui", 0x0000002DU, 1, {reg_t,gap,gap,gap,gap}, OPERAND_FIRST,0xFFF00},
	{ NULL,NULL, 0, 0, 0}
};

const apex_opc_info_t apex_APC_32b_vector_opc_info[] =
{
				/*Vector Stack Instructions*/
	{   "vcspush", 0x400002C8U, OPERAND_s0},
	{    "vcspop", 0x400002D0U, NONE_OPERAND},
	{   "vcsflip", 0x400002D8U, NONE_OPERAND},
	{   "vcsfpop", 0x400002E0U, NONE_OPERAND},
	{    "vcsref", 0x400002F0U, OPERAND_s0},
	{"vcsinvrefine", 0x400002e8U, OPERAND_i0},
	{"vcsptr_get", 0x40000388U, OPERAND_FIRST},
	{"vcsptr_inc", 0x40000380U, NONE_OPERAND},
	{"vcsptr_set", 0x40000390U, SHIFT_RIGHT(OPERAND_i0,3)},
	{   "vcs_set", 0x40000378U, NONE_OPERAND},
	{      "vcmv", 0x402805D8U, OPERAND_d0},
	{     "vcinv", 0x402805D0U, OPERAND_d0},
	/*{ "vcspush_l", 0x00000000U, 0x00000000U}, //TODO short instr
	{ "vcspush_l", 0x00000000U, 0x00000000U}, //TODO short instr
	{    "vcspop", 0x00000000U, 0x00000000U}, //TODO short instr
	{   "vcsflip", 0x00000000U, 0x00000000U}, //TODO short instr
	{   "vcsfpop", 0x00000000U, 0x00000000U}, //TODO short instr
	{    "vcsnop", 0x00000000U, 0x00000000U}, *///TODO short instr
				/*Vector Memory LD/ST instructions*/
	{    	"vlb", 0x00000000U, 0x00000000U},
	{      "vlbu", 0x00000000U, 0x00000000U},
	{       "vlw", 0x00000000U, 0x00000000U},
	{    	"vsb", 0x00000000U, 0x00000000U},
	{    	"vsw", 0x00000000U, 0x00000000U},
	{      "vclb", 0x00000000U, 0x00000000U},
	{      "vclw", 0x00000000U, 0x00000000U},
	{      "vcsw", 0x00000000U, 0x00000000U},
	{   "vlbpost", 0x00000000U, 0x00000000U},
	{  "vlbupost", 0x00000000U, 0x00000000U},
	{   "vlwpost", 0x00000000U, 0x00000000U},
	{   "vsbpost", 0x00000000U, 0x00000000U},
	{   "vswpost", 0x00000000U, 0x00000000U},
	{      "vilb", 0x00000000U, 0x00000000U},
	{     "vilbu", 0x00000000U, 0x00000000U},
	{      "vilw", 0x00000000U, 0x00000000U},
	{      "visb", 0x00000000U, 0x00000000U},
	{      "visw", 0x00000000U, 0x00000000U},
			/*Vector ALU instructions*/
	{      "vadd", 0x00000000U, 0x00000000U},
	{     "vaddx", 0x00000000U, 0x00000000U},
	{      "vadd", 0x00000000U, 0x00000000U},
	{     "vaddx", 0x00000000U, 0x00000000U},
	{      "vadd", 0x00000000U, 0x00000000U},
	{     "vaddx", 0x00000000U, 0x00000000U},
	{      "vadd", 0x00000000U, 0x00000000U},
	{     "vaddx", 0x00000000U, 0x00000000U},
	{      "vadd", 0x00000000U, 0x00000000U},
	{     "vaddx", 0x00000000U, 0x00000000U},
	{      "vsub", 0x00000000U, 0x00000000U},
	{     "vsubx", 0x00000000U, 0x00000000U},
	{      "vsub", 0x00000000U, 0x00000000U},
	{     "vsubx", 0x00000000U, 0x00000000U},
	{     "vsubr", 0x00000000U, 0x00000000U},
	{      "vsub", 0x00000000U, 0x00000000U},
	{     "vsubx", 0x00000000U, 0x00000000U},
	{      "vsub", 0x00000000U, 0x00000000U},
	{     "vsubx", 0x00000000U, 0x00000000U},
	{      "vand", 0x00000000U, 0x00000000U},
	{       "vor", 0x00000000U, 0x00000000U},
	{      "vxor", 0x00000000U, 0x00000000U},
	{       "vor", 0x00000000U, 0x00000000U},
	{      "vxor", 0x00000000U, 0x00000000U},
	{      "vand", 0x00000000U, 0x00000000U},
	{       "vor", 0x00000000U, 0x00000000U},
	{      "vxor", 0x00000000U, 0x00000000U},
	{      "vxtd", 0x00000000U, 0x00000000U},
	{      "vxtd", 0x00000000U, 0x00000000U},
	{      "vxtd", 0x00000000U, 0x00000000U},
	{   "vhadduu", 0x00000000U, 0x00000000U},
	{   "vhadduu", 0x00000000U, 0x00000000U},
	{   "vhaddss", 0x00000000U, 0x00000000U},
	{   "vhaddss", 0x00000000U, 0x00000000U},
	{  "vrhadduu", 0x00000000U, 0x00000000U},
	{  "vrhadduu", 0x00000000U, 0x00000000U},
	{  "vrhaddss", 0x00000000U, 0x00000000U},
	{  "vrhaddss", 0x00000000U, 0x00000000U},
	{ "vabs_diff", 0x00000000U, 0x00000000U},
	{ "vabs_diff", 0x00000000U, 0x00000000U},
	{"vabs_diffu", 0x00000000U, 0x00000000U},
	{"vabs_diffu", 0x00000000U, 0x00000000U},
	{  "vadd_sat", 0x00000000U, 0x00000000U},
	{  "vadd_sat", 0x00000000U, 0x00000000U},
	{ "vadd_satu", 0x00000000U, 0x00000000U},
	{ "vadd_satu", 0x00000000U, 0x00000000U},
	{  "vsub_sat", 0x00000000U, 0x00000000U},
	{  "vsub_sat", 0x00000000U, 0x00000000U},
	{ "vsub_satu", 0x00000000U, 0x00000000U},
	{ "vsub_satu", 0x00000000U, 0x00000000U},
	{      "vsat", 0x00000000U, 0x00000000U},
	{      "vsat", 0x00000000U, 0x00000000U},
	{      "vsat", 0x00000000U, 0x00000000U},
	{      "vsat", 0x00000000U, 0x00000000U},
	{      "vabs", 0x00000000U, 0x00000000U},
	{      "vclz", 0x00000000U, 0x00000000U},
	{      "vcld", 0x00000000U, 0x00000000U},
	{     "vpcnt", 0x00000000U, 0x00000000U},
	{   "vacc32u", 0x00000000U, 0x00000000U},
	{"vacc32u_sl8", 0x00000000U, 0x00000000U},
	{   "vacc32s", 0x00000000U, 0x00000000U},
	{"vacc32s_sl8", 0x00000000U, 0x00000000U},
	{      "vasb", 0x00000000U, 0x00000000U},
	{      "vasb", 0x00000000U, 0x00000000U},
	{      "vasb", 0x00000000U, 0x00000000U},
	{     "vasbs", 0x00000000U, 0x00000000U},
	{     "vasbs", 0x00000000U, 0x00000000U},
	{     "vasbs", 0x00000000U, 0x00000000U},
			/*Vector multiplication instructions*/
	{ "vmul_lulu", 0x00000000U, 0x00000000U},
	{ "vmul_lslu", 0x00000000U, 0x00000000U},
	{ "vmul_lsls", 0x00000000U, 0x00000000U},
	{ "vmul_hulu", 0x00000000U, 0x00000000U},
	{ "vmul_huls", 0x00000000U, 0x00000000U},
	{ "vmul_hslu", 0x00000000U, 0x00000000U},
	{ "vmul_hsls", 0x00000000U, 0x00000000U},
	{ "vmul_huhu", 0x00000000U, 0x00000000U},
	{ "vmul_hshu", 0x00000000U, 0x00000000U},
	{ "vmul_hshs", 0x00000000U, 0x00000000U},
	{      "vmul", 0x00000000U, 0x00000000U},
	{ "vmul_lulu", 0x00000000U, 0x00000000U},
	{ "vmul_lslu", 0x00000000U, 0x00000000U},
	{ "vmul_lsls", 0x00000000U, 0x00000000U},
	{ "vmul_hulu", 0x00000000U, 0x00000000U},
	{ "vmul_huls", 0x00000000U, 0x00000000U},
	{ "vmul_hslu", 0x00000000U, 0x00000000U},
	{ "vmul_hsls", 0x00000000U, 0x00000000U},
	{ "vmul_huhu", 0x00000000U, 0x00000000U},
	{ "vmul_hshu", 0x00000000U, 0x00000000U},
	{ "vmul_hshs", 0x00000000U, 0x00000000U},
	{      "vmul", 0x00000000U, 0x00000000U},
	{ "vmul_lslu", 0x00000000U, 0x00000000U},
	{ "vmul_hulu", 0x00000000U, 0x00000000U},
	{ "vmul_huls", 0x00000000U, 0x00000000U},
	{ "vmul_hslu", 0x00000000U, 0x00000000U},
	{ "vmul_hsls", 0x00000000U, 0x00000000U},
	{ "vmul_hshu", 0x00000000U, 0x00000000U},
	{     "vimul", 0x00000000U, 0x00000000U},
	{      "vsll", 0x00000000U, 0x00000000U},
	{      "vsra", 0x00000000U, 0x00000000U},
	{      "vsrl", 0x00000000U, 0x00000000U},
	{     "vssla", 0x00000000U, 0x00000000U},
	{     "vssll", 0x00000000U, 0x00000000U},
	{       "vrl", 0x00000000U, 0x00000000U},
	{      "vsll", 0x00000000U, 0x00000000U},
	{      "vsra", 0x00000000U, 0x00000000U},
	{      "vsrl", 0x00000000U, 0x00000000U},
	{     "vssla", 0x00000000U, 0x00000000U},
	{     "vssll", 0x00000000U, 0x00000000U},
	{       "vrl", 0x00000000U, 0x00000000U},
	{      "vsll", 0x00000000U, 0x00000000U},
	{      "vsra", 0x00000000U, 0x00000000U},
	{     "vssla", 0x00000000U, 0x00000000U},
	{     "vssll", 0x00000000U, 0x00000000U},
	{      "vsrl", 0x00000000U, 0x00000000U},
	{       "vrl", 0x00000000U, 0x00000000U},
	{   "vsrl_ov", 0x00000000U, 0x00000000U},
	{   "vsll_ov", 0x00000000U, 0x00000000U},
	{   "vsrl_vc", 0x00000000U, 0x00000000U},
	{   "vsll_vc", 0x00000000U, 0x00000000U},
	{    "vsllxi", 0x00000000U, 0x00000000U},
	{    "vsraxi", 0x00000000U, 0x00000000U},
	{    "vsrlxi", 0x00000000U, 0x00000000U},
	{     "vsllx", 0x00000000U, 0x00000000U},
	{     "vsrax", 0x00000000U, 0x00000000U},
	{     "vsrlx", 0x00000000U, 0x00000000U},
	{     "vsllx", 0x00000000U, 0x00000000U},
	{     "vsrax", 0x00000000U, 0x00000000U},
	{     "vsrlx", 0x00000000U, 0x00000000U},
	{       "vmv", 0x00000000U, 0x00000000U},
	{      "vmv2", 0x00000000U, 0x00000000U},
	{       "vli", 0x00000000U, 0x00000000U},
	{     "vmrhi", 0x00000000U, 0x00000000U},
	{      "vmrh", 0x00000000U, 0x00000000U},
	{      "vmrb", 0x00000000U, 0x00000000U},
	{     "vmrbu", 0x00000000U, 0x00000000U},
			/*Vector condition register instructions*/
	{     "vcand", 0x00000000U, 0x00000000U},
	{      "vcor", 0x00000000U, 0x00000000U},
	{     "vcxor", 0x00000000U, 0x00000000U},
	{      "vcsr", 0x00000000U, 0x00000000U},
	{      "vcsl", 0x00000000U, 0x00000000U},
	{     "vcand", 0x00000000U, 0x00000000U},
	{      "vcor", 0x00000000U, 0x00000000U},
	{     "vcxor", 0x00000000U, 0x00000000U},
	{     "vcinv", 0x00000000U, 0x00000000U},
	{      "vcmv", 0x00000000U, 0x00000000U},
	{      "vcsr", 0x00000000U, 0x00000000U},
	{      "vcsl", 0x00000000U, 0x00000000U},
	{      "vmvc", 0x00000000U, 0x00000000U},
	{      "vmvc", 0x00000000U, 0x00000000U},
	{       "vwe", 0x00000000U, 0x00000000U},
	{       "vwe", 0x00000000U, 0x00000000U},
	{       "vwe", 0x00000000U, 0x00000000U},
	{       "vwe", 0x00000000U, 0x00000000U},
	{       "vwe", 0x00000000U, 0x00000000U},
	{      "vexi", 0x00000000U, 0x00000000U},
	{     "vexiu", 0x00000000U, 0x00000000U},
	{      "vexr", 0x00000000U, 0x00000000U},
	{     "vexru", 0x00000000U, 0x00000000U},
	{    "vex_vc", 0x00000000U, 0x00000000U},
	{      "vput", 0x00000000U, 0x00000000U},
	{      "vany", 0x00000000U, 0x00000000U},
	{      "vall", 0x00000000U, 0x00000000U},
	{      "vany", 0x00000000U, 0x00000000U},
	{      "vall", 0x00000000U, 0x00000000U},
	{      "vany", 0x00000000U, 0x00000000U},
	{      "vall", 0x00000000U, 0x00000000U},
	{      "vseq", 0x00000000U, 0x00000000U},
	{      "vsne", 0x00000000U, 0x00000000U},
	{      "vsge", 0x00000000U, 0x00000000U},
	{      "vsgt", 0x00000000U, 0x00000000U},
	{      "vsle", 0x00000000U, 0x00000000U},
	{      "vslt", 0x00000000U, 0x00000000U},
	{     "vsgeu", 0x00000000U, 0x00000000U},
	{     "vsgtu", 0x00000000U, 0x00000000U},
	{     "vsleu", 0x00000000U, 0x00000000U},
	{     "vsltu", 0x00000000U, 0x00000000U},
	{      "vseq", 0x00000000U, 0x00000000U},
	{      "vsne", 0x00000000U, 0x00000000U},
	{      "vsge", 0x00000000U, 0x00000000U},
	{      "vsgt", 0x00000000U, 0x00000000U},
	{      "vsle", 0x00000000U, 0x00000000U},
	{      "vslt", 0x00000000U, 0x00000000U},
	{     "vsgeu", 0x00000000U, 0x00000000U},
	{     "vsgtu", 0x00000000U, 0x00000000U},
			/*Vector pointer modification instructions*/
	{      "padd", 0x00000000U, 0x00000000U},
	{       "add", 0x00000000U, 0x00000000U},
	{       "add", 0x00000000U, 0x00000000U},
	{       "mov", 0x00000000U, 0x00000000U},
			/*Vector to vector movement*/
	{     "vmrlv", 0x00000000U, 0x00000000U},
	{     "vmrrv", 0x00000000U, 0x00000000U},
	{     "vmrlr", 0x00000000U, 0x00000000U},
	{     "vmrrr", 0x00000000U, 0x00000000U},
			/*Vector swap*/
	{     "vspge", 0x00000000U, 0x00000000U},
	{     "vspgt", 0x00000000U, 0x00000000U},
	{     "vsple", 0x00000000U, 0x00000000U},
	{     "vsplt", 0x00000000U, 0x00000000U},
	{    "vspgeu", 0x00000000U, 0x00000000U},
	{    "vspgtu", 0x00000000U, 0x00000000U},
	{    "vspleu", 0x00000000U, 0x00000000U},
	{    "vspltU", 0x00000000U, 0x00000000U},
	{  "VSWAP_Op", 0x00000000U, 0x00000000U},
	{      "vsel", 0x00000000U, 0x00000000U},
	{      "vsel", 0x00000000U, 0x00000000U},
	{     "vsleu", 0x00000000U, 0x00000000U},
	{     "vsltu", 0x00000000U, 0x00000000U},
	{      "vsle", 0x00000000U, 0x00000000U},
	{      "vsle", 0x00000000U, 0x00000000U},
	{ NULL, 0, 0, 0}
};

/*Scalar-Vector combined instructions*/
//TODO:

