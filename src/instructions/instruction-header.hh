#pragma once

#include "Instruction.hh"

/// Data Transfer Instructions --------------------------------------------------------------------------------------///
#include "dataTransferInstr/MovInstr.hh"
#include "dataTransferInstr/PushInstr.hh"
#include "dataTransferInstr/PopInstr.hh"

#include "dataTransferInstr/LeaInstr.hh"

/// Arithmetic Instructions -----------------------------------------------------------------------------------------///
#include "arithmeticInstr/AddInstr.hh"

#include "arithmeticInstr/CmpInstr.hh"

/// Logic Instructions ----------------------------------------------------------------------------------------------///
#include "logicInstr/TestInstr.hh"

#include "logicInstr/XorInstr.hh"

/// String Manipulation Instructions --------------------------------------------------------------------------------///

/// Control Transfer Instructions -----------------------------------------------------------------------------------///
#include "controlTransferInstr/IntInstr.hh"

#include "controlTransferInstr/JneJnzInstr.hh"

#include "controlTransferInstr/JnbJnaInstr.hh"
