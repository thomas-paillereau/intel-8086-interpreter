#pragma once

#include "Instruction.hh"

/// Data Transfer Instructions --------------------------------------------------------------------------------------///
#include "dataTransferInstr/MovInstr.hh"
#include "dataTransferInstr/PushInstr.hh"
#include "dataTransferInstr/PopInstr.hh"

#include "dataTransferInstr/LeaInstr.hh"

/// Arithmetic Instructions -----------------------------------------------------------------------------------------///
#include "arithmeticInstr/AddInstr.hh"

#include "arithmeticInstr/DecInstr.hh"

#include "arithmeticInstr/CmpInstr.hh"

/// Logic Instructions ----------------------------------------------------------------------------------------------///
#include "logicInstr/TestInstr.hh"

#include "logicInstr/XorInstr.hh"

/// String Manipulation Instructions --------------------------------------------------------------------------------///

/// Control Transfer Instructions -----------------------------------------------------------------------------------///
#include "controlTransferInstr/CallInstr.hh"
#include "controlTransferInstr/JmpInstr.hh"

#include "controlTransferInstr/JneJnzInstr.hh"

#include "controlTransferInstr/JnbJnaInstr.hh"

#include "controlTransferInstr/IntInstr.hh"

/// Processor Control Instructions
#include "processorControlInstr/HltInstr.hh"
