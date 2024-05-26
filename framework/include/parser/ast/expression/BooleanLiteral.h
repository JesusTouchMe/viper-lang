// Copyright 2024 solar-mist

#ifndef VIPER_FRAMEWORK_PARSER_AST_EXPRESSION_BOOLEAN_LITERAL_H
#define VIPER_FRAMEWORK_PARSER_AST_EXPRESSION_BOOLEAN_LITERAL_H 1

#include "parser/ast/Node.h"

namespace parser
{
    class BooleanLiteral : public ASTNode
    {
    public:
        BooleanLiteral(bool value, lexing::Token token);

        bool getValue() const;

        void typeCheck(Scope* scope, diagnostic::Diagnostics& diag) override;
        vipir::Value* emit(vipir::IRBuilder& builder, vipir::Module& module, Scope* scope, diagnostic::Diagnostics& diag) override;

    private:
        bool mValue;
    };
    using BooleanLiteralPtr = std::unique_ptr<BooleanLiteral>;
}

#endif // VIPER_FRAMEWORK_PARSER_AST_EXPRESSION_BOOLEAN_LITERAL_H