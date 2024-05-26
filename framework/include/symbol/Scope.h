// Copyright 2024 solar-mist


#ifndef VIPER_FRAMEWORK_SYMBOL_SCOPE_H
#define VIPER_FRAMEWORK_SYMBOL_SCOPE_H 1

#include "type/StructType.h"
#include "type/FunctionType.h"

#include <vipir/IR/Instruction/AllocaInst.h>
#include <vipir/IR/Function.h>
#include <vipir/IR/GlobalVar.h>

#include <optional>
#include <unordered_map>

struct LocalSymbol
{
    LocalSymbol() = default;
    LocalSymbol(vipir::AllocaInst* alloca, Type* type);

    vipir::Value* alloca;
    Type* type;
};

struct FunctionSymbol
{
    FunctionSymbol() = default;
    FunctionSymbol(vipir::Function* function, Type* type, bool priv, bool mangle = true);

    vipir::Function* function;
    std::vector<std::string> names;
    bool priv;
    bool mangle;
    FunctionType* type;

    static void Create(vipir::Function* function, std::string mangledName, std::vector<std::string> names, Type* type, bool priv, bool mangle = true);
};
struct GlobalSymbol
{
    GlobalSymbol() = default;
    GlobalSymbol(vipir::Value* global, Type* type);

    vipir::Value* global;
    Type* type;
};
extern std::unordered_map<std::string, FunctionSymbol> GlobalFunctions;
extern std::unordered_map<std::string, GlobalSymbol> GlobalVariables;
FunctionSymbol* FindFunction(std::vector<std::string> givenNames, std::vector<std::string> activeNames, std::vector<Type*> arguments);

struct Scope
{
    Scope(Scope* parent, StructType* owner);

    std::unordered_map<std::string, LocalSymbol> locals;

    LocalSymbol* findVariable(const std::string& name);
    vipir::BasicBlock* findBreakBB();
    vipir::BasicBlock* findContinueBB();
    StructType* findOwner();
    std::vector<std::string> getNamespaces();

    Scope* parent;
    StructType* owner;
    Type* currentReturnType;
    vipir::BasicBlock* breakTo;
    vipir::BasicBlock* continueTo;
    std::string namespaceName;
};
using ScopePtr = std::unique_ptr<Scope>;

#endif // VIPER_FRAMEWORK_SYMBOL_SCOPE_H