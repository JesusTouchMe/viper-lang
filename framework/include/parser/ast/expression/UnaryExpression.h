#ifndef VIPER_FRAMEWORK_PARSER_AST_EXPRESSION_UNARY_EXPRESSION_H
#define VIPER_FRAMEWORK_PARSER_AST_EXPRESSION_UNARY_EXPRESSION_H 1

#include "parser/ast/ASTNode.h"

#include <memory>

namespace parser
{
    class UnaryExpression : public ASTNode
    {
    public:
        enum class Operator 
        {
            Negate,
        };

        UnaryExpression(Scope* scope, ASTNodePtr operand, lexer::TokenType operatorToken, bool postfix, lexer::Token token);

        virtual vipir::Value* codegen(vipir::IRBuilder& builder, vipir::Module& module, diagnostic::Diagnostics& diag) override;

        virtual void typeCheck(diagnostic::Diagnostics& diag, bool& exit) override;
        virtual bool implicitCast(diagnostic::Diagnostics& diag, Type* destType) override;
        virtual bool triviallyImplicitCast(diagnostic::Diagnostics& diag, Type* destType) override;

    private:
        ASTNodePtr mOperand;
        Operator mOperator;
        bool mPostfix;
    };
    using UnaryExpressionPtr = std::unique_ptr<UnaryExpression>;
}

#endif // VIPER_FRAMEWORK_PARSER_AST_EXPRESSION_UNARY_EXPRESSION_H