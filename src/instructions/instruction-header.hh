#pragma once

#include "Instruction.hh"

/// Data Transfer Instructions --------------------------------------------------------------------------------------///
#include "dataTransferInstr/MovInstr.hh"
#include "dataTransferInstr/PushInstr.hh"
#include "dataTransferInstr/PopInstr.hh"
#include "dataTransferInstr/XchgInstr.hh"
#include "dataTransferInstr/InInstr.hh"
// OUT
// XLAT
#include "dataTransferInstr/LeaInstr.hh"
// LDS
// LES
// LAHF
// SAHF
// PUSHF
// POPF

/// Arithmetic Instructions -----------------------------------------------------------------------------------------///
#include "arithmeticInstr/AddInstr.hh"
#include "arithmeticInstr/AdcInstr.hh"
#include  "arithmeticInstr/IncInstr.hh"
// AAA
// BAA
#include "arithmeticInstr/SubInstr.hh"
#include "arithmeticInstr/SbbInstr.hh"
#include "arithmeticInstr/DecInstr.hh"
#include "arithmeticInstr/NegInstr.hh"
#include "arithmeticInstr/CmpInstr.hh"
// AAS
// DAS
#include "arithmeticInstr/MulInstr.hh"
// IMUL
// AAM
#include "arithmeticInstr/DivInstr.hh"
// IDIV
// AAD
#include "arithmeticInstr/CbwInstr.hh"
#include "arithmeticInstr/CwdInstr.hh"

/// Logic Instructions ----------------------------------------------------------------------------------------------///
// NOT
#include "logicInstr/ShlSalInstr.hh"
#include "logicInstr/ShrInstr.hh"
#include "logicInstr/SarInstr.hh"
// ROL
// ROR
#include "logicInstr/RclInstr.hh"
// RCR
#include "logicInstr/AndInstr.hh"
#include "logicInstr/TestInstr.hh"
#include "logicInstr/OrInstr.hh"
#include "logicInstr/XorInstr.hh"

/// String Manipulation Instructions --------------------------------------------------------------------------------///
#include "stringManipulationInstr/RepInstr.hh"
#include "stringManipulationInstr/MovsInstr.hh"
// CMPS
// SCAS
// LODS
// STOS

/// Control Transfer Instructions -----------------------------------------------------------------------------------///
#include "controlTransferInstr/CallInstr.hh"
#include "controlTransferInstr/JmpInstr.hh"
#include "controlTransferInstr/RetInstr.hh"
#include "controlTransferInstr/JeJzInstr.hh"
#include "controlTransferInstr/JlJngeInstr.hh"
#include "controlTransferInstr/JlejngInstr.hh"
#include "controlTransferInstr/JbJnaeInstr.hh"
#include "controlTransferInstr/JbeJnaInstr.hh"
// JP/JPE
// JO
// JS
#include "controlTransferInstr/JneJnzInstr.hh"
#include "controlTransferInstr/JnlJgeInstr.hh"
#include "controlTransferInstr/JnleJgInstr.hh"
#include "controlTransferInstr/JnbJaeInstr.hh"
#include "controlTransferInstr/JnbeJaInstr.hh"
// JNP/JPO
// JNO
// JNS
#include "controlTransferInstr/LoopInstr.hh"
// LOOPZ/LOOPE
// LOOPNZ/LOOPNE
// JCXZ
#include "controlTransferInstr/IntInstr.hh"
// INTO
// IRET

/// Processor Control Instructions
// CLC
// CMC
// STC
#include "processorControlInstr/CldInstr.hh"
#include "processorControlInstr/StdInstr.hh"
// CLI
// STI
#include "processorControlInstr/HltInstr.hh"
// WAIT
// ESC
// LOCK
