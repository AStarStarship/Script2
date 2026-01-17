// Copyright AStarship <https://astarship.net>.
#include <_Config.h>
//
#include "../_Package.hxx"
//
#include "01.COut.hxx"
#include "02.ItoS.hxx"
#include "03.FtoS.hxx"
#include "04.Uniprinter.hxx"
#include "05.Clock.hxx"
#include "06.Array.hxx"
#include "07.Stack.hxx"
#include "08.String.hxx"
#include "09.Loom.hxx"
#include "10.List.hxx"
#include "11.Book.hxx"
#include "12.Map.hxx"
#include "13.Table.hxx"
#include "14.Dic.hxx"
#include "15.MathCore.hxx"
#include "16.RNG.hxx"
#include "17.File.hxx"
#include "18.SGraTe.hxx"
#include "19.CrabsOp.hxx"
#include "20.Room.hxx"
#include "21.Script2Core.hxx"
#include "22.Release.hxx"
//
#include "../Test.hpp"
using namespace ::_;

inline const CHA* Script2Tests(const CHA* args) {
  return TTestTree<Script2::COut, Script2::ItoS, Script2::FtoS, 
    Script2::Uniprinter, Script2::Clock, Script2::Stack, Script2::String, 
    Script2::Loom,  Script2::List, Script2::Book, Script2::Map, Script2::Table,
    Script2::Dic, Script2::MathCore, Script2::RNG, Script2::File,
    Script2::SGraTe, Script2::CrabsOp, Script2::Room, 
    Script2::Script2Core>(args);
}
