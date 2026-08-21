#pragma once

#include "Instruction.hh"

/// Data Transfer Instructions --------------------------------------------------------------------------------------///
#include "dataTransferInstr/MovInstr.hh"
#include "dataTransferInstr/PushInstr.hh"
#include "dataTransferInstr/PopInstr.hh"
#include "dataTransferInstr/XchgInstr.hh"
#include "dataTransferInstr/InInstr.hh"

#include "dataTransferInstr/LeaInstr.hh"

/// Arithmetic Instructions -----------------------------------------------------------------------------------------///
#include "arithmeticInstr/AddInstr.hh"
#include "arithmeticInstr/AdcInstr.hh"
#include  "arithmeticInstr/IncInstr.hh"

#include "arithmeticInstr/SubInstr.hh"
#include "arithmeticInstr/SbbInstr.hh"
#include "arithmeticInstr/DecInstr.hh"
#include "arithmeticInstr/NegInstr.hh"
#include "arithmeticInstr/CmpInstr.hh"

#include "arithmeticInstr/MulInstr.hh"

#include "arithmeticInstr/DivInstr.hh"

#include "arithmeticInstr/CbwInstr.hh"
#include "arithmeticInstr/CwdInstr.hh"

/// Logic Instructions ----------------------------------------------------------------------------------------------///
#include "logicInstr/ShlSalInstr.hh"
#include "logicInstr/ShrInstr.hh"
#include "logicInstr/SarInstr.hh"

#include "logicInstr/RclInstr.hh"

#include "logicInstr/AndInstr.hh"
#include "logicInstr/TestInstr.hh"
#include "logicInstr/OrInstr.hh"
#include "logicInstr/XorInstr.hh"

/// String Manipulation Instructions --------------------------------------------------------------------------------///
#include "stringManipulationInstr/RepInstr.hh"

/// Control Transfer Instructions -----------------------------------------------------------------------------------///
#include "controlTransferInstr/CallInstr.hh"
#include "controlTransferInstr/JmpInstr.hh"
#include "controlTransferInstr/RetInstr.hh"
#include "controlTransferInstr/JeJzInstr.hh"
#include "controlTransferInstr/JlJngeInstr.hh"
#include "controlTransferInstr/JlejngInstr.hh"
#include "controlTransferInstr/JbJnaeInstr.hh"
#include "controlTransferInstr/JbeJnaInstr.hh"

#include "controlTransferInstr/JneJnzInstr.hh"
#include "controlTransferInstr/JnlJgeInstr.hh"
#include "controlTransferInstr/JnleJgInstr.hh"
#include "controlTransferInstr/JnbJaeInstr.hh"
#include "controlTransferInstr/JnbeJaInstr.hh"

#include "controlTransferInstr/LoopInstr.hh"

#include "controlTransferInstr/IntInstr.hh"

/// Processor Control Instructions
#include "processorControlInstr/CldInstr.hh"
#include "processorControlInstr/StdInstr.hh"

#include "processorControlInstr/HltInstr.hh"
