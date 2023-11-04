#include <iostream>
#include <memory>

#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/DebugInfoMetadata.h"

using namespace llvm;

int
main (int argc, char *argv[])
{
  LLVMContext context;
  SMDiagnostic error;
  if (argc < 2)
    {
      std::cout << "Usage: " << argv[0] << " <IR file>" << std::endl;
      exit (1);
    }

  std::string filename = argv[1];
  std::unique_ptr<Module> module = parseIRFile (filename, error, context);

  if (!module)
    {
      std::cout << "Error: " << error.getMessage ().str () << " at "
		<< error.getFilename ().str () << ":" << error.getLineNo ()
		<< ":" << error.getColumnNo () << std::endl;
      exit (1);
    }

  for (auto &func : module->getFunctionList ())
    {
      DISubprogram *sub = func.getSubprogram ();

      if (!func.hasName () || sub == nullptr)
	continue;

      std::string qpath = sub->getName ().str ();

      DIScope *scope = sub->getScope ();
      while (scope != nullptr)
	{
	  qpath = scope->getName ().str () + "::" + qpath;
	  scope = scope->getScope ();
	}

      std::cout << qpath << " → " << sub->getLinkageName ().str () << std::endl;
    }
}
