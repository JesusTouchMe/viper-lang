// Copyright 2024 solar-mist

#ifndef VIPER_FRAMEWORK_PARSER_AST_GLOBAL_FUNCTION_H
#define VIPER_FRAMEWORK_PARSER_AST_GLOBAL_FUNCTION_H 1

#include "parser/ast/Node.h"

#include "parser/ast/global/GlobalAttribute.h"

namespace parser
{
    struct FunctionArgument
    {
        std::string name;
        Type* type;
    };

    class Function : public ASTNode
    {
    public:
        Function(std::vector<GlobalAttribute> attributes, Type* type, std::vector<FunctionArgument> arguments, std::string_view name, std::vector<ASTNodePtr>&& body, Scope* scope);

        Type* getReturnType() const;

        void typeCheck(Scope* scope, diagnostic::Diagnostics& diag) override;
        vipir::Value* emit(vipir::IRBuilder& builder, vipir::Module& module, Scope* scope, diagnostic::Diagnostics& diag) override;

    private:
        std::vector<GlobalAttribute> mAttributes;

        Type* mType;
        std::vector<FunctionArgument> mArguments;
        std::string mName;
        std::vector<ASTNodePtr> mBody;
        ScopePtr mScope;
    };
    using FunctionPtr = std::unique_ptr<Function>;
}

#endif // VIPER_FRAMEWORK_PARSER_AST_GLOBAL_FUNCTION_H
