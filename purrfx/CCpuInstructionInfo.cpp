#include "CCpuInstructionInfo.h"

PurrFX::CCpuInstructionInfo::CCpuInstructionInfo(uint8_t i_nOpcode):
	m_nOpcode(i_nOpcode)
{
}

const char* PurrFX::CCpuInstructionInfo::name() const
{
	switch (m_nOpcode)
	{
		// ADC
	case 0x69: return "ADC";
	case 0x65: return "ADC";
	case 0x75: return "ADC";
	case 0x6D: return "ADC";
	case 0x7D: return "ADC";
	case 0x79: return "ADC";
	case 0x61: return "ADC";
	case 0x71: return "ADC";
		// AND
	case 0x29: return "AND";
	case 0x25: return "AND";
	case 0x35: return "AND";
	case 0x2D: return "AND";
	case 0x3D: return "AND";
	case 0x39: return "AND";
	case 0x21: return "AND";
	case 0x31: return "AND";
		// ASL
	case 0x0A: return "ASL";
	case 0x06: return "ASL";
	case 0x16: return "ASL";
	case 0x0E: return "ASL";
	case 0x1E: return "ASL";
		// BIT
	case 0x24: return "BIT";
	case 0x2C: return "BIT";
		// Bxx
	case 0x10: return "BPL";
	case 0x30: return "BMI";
	case 0x50: return "BVC";
	case 0x70: return "BVS";
	case 0x90: return "BCC";
	case 0xB0: return "BCS";
	case 0xD0: return "BNE";
	case 0xF0: return "BEQ";
		// BRK
	case 0x00: return "BRK";
		// CMP
	case 0xC9: return "CMP";
	case 0xC5: return "CMP";
	case 0xD5: return "CMP";
	case 0xCD: return "CMP";
	case 0xDD: return "CMP";
	case 0xD9: return "CMP";
	case 0xC1: return "CMP";
	case 0xD1: return "CMP";
		// CPX
	case 0xE0: return "CPX";
	case 0xE4: return "CPX";
	case 0xEC: return "CPX";
		// CPY
	case 0xC0: return "CPY";
	case 0xC4: return "CPY";
	case 0xCC: return "CPY";
		// DEC
	case 0xC6: return "DEC";
	case 0xD6: return "DEC";
	case 0xCE: return "DEC";
	case 0xDE: return "DEC";
		// EOR
	case 0x49: return "EOR";
	case 0x45: return "EOR";
	case 0x55: return "EOR";
	case 0x4D: return "EOR";
	case 0x5D: return "EOR";
	case 0x59: return "EOR";
	case 0x41: return "EOR";
	case 0x51: return "EOR";
		// Flag instructions
	case 0x18: return "CLC";
	case 0x38: return "SEC";
	case 0x58: return "CLI";
	case 0x78: return "SEI";
	case 0xB8: return "CLV";
	case 0xD8: return "CLD";
	case 0xF8: return "SED";
		// INC
	case 0xE6: return "INC";
	case 0xF6: return "INC";
	case 0xEE: return "INC";
	case 0xFE: return "INC";
		// JMP
	case 0x4C: return "JMP";
	case 0x6C: return "JMP";
		// JSR
	case 0x20: return "JSR";
		// LDA
	case 0xA9: return "LDA";
	case 0xA5: return "LDA";
	case 0xB5: return "LDA";
	case 0xAD: return "LDA";
	case 0xBD: return "LDA";
	case 0xB9: return "LDA";
	case 0xA1: return "LDA";
	case 0xB1: return "LDA";
		// LDX
	case 0xA2: return "LDX";
	case 0xA6: return "LDX";
	case 0xB6: return "LDX";
	case 0xAE: return "LDX";
	case 0xBE: return "LDX";
		// LDY
	case 0xA0: return "LDY";
	case 0xA4: return "LDY";
	case 0xB4: return "LDY";
	case 0xAC: return "LDY";
	case 0xBC: return "LDY";
		// LSR
	case 0x4A: return "LSR";
	case 0x46: return "LSR";
	case 0x56: return "LSR";
	case 0x4E: return "LSR";
	case 0x5E: return "LSR";
		// NOP
	case 0xEA: return "NOP";
		// ORA
	case 0x09: return "ORA";
	case 0x05: return "ORA";
	case 0x15: return "ORA";
	case 0x0D: return "ORA";
	case 0x1D: return "ORA";
	case 0x19: return "ORA";
	case 0x01: return "ORA";
	case 0x11: return "ORA";
		// Register Instructions 
	case 0xAA: return "TAX";
	case 0x8A: return "TXA";
	case 0xCA: return "DEX";
	case 0xE8: return "INX";
	case 0xA8: return "TAY";
	case 0x98: return "TYA";
	case 0x88: return "DEY";
	case 0xC8: return "INY";
		// ROL
	case 0x2A: return "ROL";
	case 0x26: return "ROL";
	case 0x36: return "ROL";
	case 0x2E: return "ROL";
	case 0x3E: return "ROL";
		// ROR
	case 0x6A: return "ROR";
	case 0x66: return "ROR";
	case 0x76: return "ROR";
	case 0x6E: return "ROR";
	case 0x7E: return "ROR";
		// RTI
	case 0x40: return "RTI";
		// RTS
	case 0x60: return "RTS";
		// SBC
	case 0xE9: return "SBC";
	case 0xE5: return "SBC";
	case 0xF5: return "SBC";
	case 0xED: return "SBC";
	case 0xFD: return "SBC";
	case 0xF9: return "SBC";
	case 0xE1: return "SBC";
	case 0xF1: return "SBC";
		// STA
	case 0x85: return "STA";
	case 0x95: return "STA";
	case 0x8D: return "STA";
	case 0x9D: return "STA";
	case 0x99: return "STA";
	case 0x81: return "STA";
	case 0x91: return "STA";
		// Stack Instructions
	case 0x9A: return "TXS";
	case 0xBA: return "TSX";
	case 0x48: return "PHA";
	case 0x68: return "PLA";
	case 0x08: return "PHP";
	case 0x28: return "PLP";
		// STX
	case 0x86: return "STX";
	case 0x96: return "STX";
	case 0x8E: return "STX";
		// STY
	case 0x84: return "STY";
	case 0x94: return "STY";
	case 0x8C: return "STY";
		// HLT
	case 0xF2: return "HLT";
	default:
		assert(false && "Unknown NES CPU instruction");
		return "?";
		break;
	}
}

int PurrFX::CCpuInstructionInfo::argBytes() const
{
	switch (m_nOpcode)
	{
		// ADC
	case 0x69: return 1;
	case 0x65: return 1;
	case 0x75: return 1;
	case 0x6D: return 2;
	case 0x7D: return 2;
	case 0x79: return 2;
	case 0x61: return 1;
	case 0x71: return 1;
		// AND
	case 0x29: return 1;
	case 0x25: return 1;
	case 0x35: return 1;
	case 0x2D: return 2;
	case 0x3D: return 2;
	case 0x39: return 2;
	case 0x21: return 1;
	case 0x31: return 1;
		// ASL
	case 0x0A: return 0;
	case 0x06: return 1;
	case 0x16: return 1;
	case 0x0E: return 2;
	case 0x1E: return 2;
		// BIT
	case 0x24: return 1;
	case 0x2C: return 2;
		// Bxx
	case 0x10: return 1;
	case 0x30: return 1;
	case 0x50: return 1;
	case 0x70: return 1;
	case 0x90: return 1;
	case 0xB0: return 1;
	case 0xD0: return 1;
	case 0xF0: return 1;
		// BRK
	case 0x00: return 0;
		// CMP
	case 0xC9: return 1;
	case 0xC5: return 1;
	case 0xD5: return 1;
	case 0xCD: return 2;
	case 0xDD: return 2;
	case 0xD9: return 2;
	case 0xC1: return 1;
	case 0xD1: return 1;
		// CPX
	case 0xE0: return 1;
	case 0xE4: return 1;
	case 0xEC: return 2;
		// CPY
	case 0xC0: return 1;
	case 0xC4: return 1;
	case 0xCC: return 2;
		// DEC
	case 0xC6: return 1;
	case 0xD6: return 1;
	case 0xCE: return 2;
	case 0xDE: return 2;
		// EOR
	case 0x49: return 1;
	case 0x45: return 1;
	case 0x55: return 1;
	case 0x4D: return 2;
	case 0x5D: return 2;
	case 0x59: return 2;
	case 0x41: return 1;
	case 0x51: return 1;
		// Flag instructions
	case 0x18: return 0;
	case 0x38: return 0;
	case 0x58: return 0;
	case 0x78: return 0;
	case 0xB8: return 0;
	case 0xD8: return 0;
	case 0xF8: return 0;
		// INC
	case 0xE6: return 1;
	case 0xF6: return 1;
	case 0xEE: return 2;
	case 0xFE: return 2;
		// JMP
	case 0x4C: return 2;
	case 0x6C: return 2;
		// JSR
	case 0x20: return 2;
		// LDA
	case 0xA9: return 1;
	case 0xA5: return 1;
	case 0xB5: return 1;
	case 0xAD: return 2;
	case 0xBD: return 2;
	case 0xB9: return 2;
	case 0xA1: return 1;
	case 0xB1: return 1;
		// LDX
	case 0xA2: return 1;
	case 0xA6: return 1;
	case 0xB6: return 1;
	case 0xAE: return 2;
	case 0xBE: return 2;
		// LDY
	case 0xA0: return 1;
	case 0xA4: return 1;
	case 0xB4: return 1;
	case 0xAC: return 2;
	case 0xBC: return 2;
		// LSR
	case 0x4A: return 0;
	case 0x46: return 1;
	case 0x56: return 1;
	case 0x4E: return 2;
	case 0x5E: return 2;
		// NOP
	case 0xEA: return 0;
		// ORA
	case 0x09: return 1;
	case 0x05: return 1;
	case 0x15: return 1;
	case 0x0D: return 2;
	case 0x1D: return 2;
	case 0x19: return 2;
	case 0x01: return 1;
	case 0x11: return 1;
		// Register Instructions 
	case 0xAA: return 0;
	case 0x8A: return 0;
	case 0xCA: return 0;
	case 0xE8: return 0;
	case 0xA8: return 0;
	case 0x98: return 0;
	case 0x88: return 0;
	case 0xC8: return 0;
		// ROL
	case 0x2A: return 0;
	case 0x26: return 1;
	case 0x36: return 1;
	case 0x2E: return 2;
	case 0x3E: return 2;
		// ROR
	case 0x6A: return 0;
	case 0x66: return 1;
	case 0x76: return 1;
	case 0x6E: return 2;
	case 0x7E: return 2;
		// RTI
	case 0x40: return 0;
		// RTS
	case 0x60: return 0;
		// SBC
	case 0xE9: return 1;
	case 0xE5: return 1;
	case 0xF5: return 1;
	case 0xED: return 2;
	case 0xFD: return 2;
	case 0xF9: return 2;
	case 0xE1: return 1;
	case 0xF1: return 1;
		// STA
	case 0x85: return 1;
	case 0x95: return 1;
	case 0x8D: return 2;
	case 0x9D: return 2;
	case 0x99: return 2;
	case 0x81: return 1;
	case 0x91: return 1;
		// Stack Instructions
	case 0x9A: return 0;
	case 0xBA: return 0;
	case 0x48: return 0;
	case 0x68: return 0;
	case 0x08: return 0;
	case 0x28: return 0;
		// STX
	case 0x86: return 1;
	case 0x96: return 1;
	case 0x8E: return 2;
		// STY
	case 0x84: return 1;
	case 0x94: return 1;
	case 0x8C: return 2;
		// HLT
	case 0xF2: return 0;
	default:
		assert(false && "Unknown NES CPU instruction");
		return 0;
		break;
	}
}
