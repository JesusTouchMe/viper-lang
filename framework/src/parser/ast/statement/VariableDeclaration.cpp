// Copyright 2024 solar-mist

#include "parser/ast/statement/VariableDeclaration.h"

#include <vipir/IR/Instruction/AllocaInst.h>
#include <vipir/IR/Instruction/StoreInst.h>

namespace parser
{
    VariableDeclaration::VariableDeclaration(Type* type, std::string&& name, ASTNodePtr&& initialValue)
        : mName(std::move(name))
        , mInitialValue(std::move(initialValue))
    {
        mType = type;
    }

    vipir::Value* VariableDeclaration::emit(vipir::IRBuilder& builder, vipir::Module& module, Scope* scope)
    {
        vipir::AllocaInst* alloca = builder.CreateAlloca(mType->getVipirType(), mName);

        if (mInitialValue)
        {
            vipir::Value* initalValue = mInitialValue->emit(builder, module, scope);
            builder.CreateStore(alloca, initalValue);
        }

        scope->locals[mName] = LocalSymbol(alloca);

        return nullptr;
    }

}