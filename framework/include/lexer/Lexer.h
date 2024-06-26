// Copyright 2024 solar-mist

#ifndef VIPER_FRAMEWORK_LEXER_LEXER_H
#define VIPER_FRAMEWORK_LEXER_LEXER_H

#include "diagnostic/Diagnostic.h"

#include <optional>
#include <string>
#include <vector>

namespace lexing
{
    class Token;
    class SourceLocation;

    class Lexer
    {
    public:
        Lexer(const std::string& text, diagnostic::Diagnostics& diag);

        std::vector<Token> lex();
    private:
        std::string mText;
        diagnostic::Diagnostics& mDiag;
        int mPosition{ 0 };
        int mColumn{ 1 };
        int mLine{ 1 };

        char current();
        char consume();
        char peek(int offset);

        SourceLocation location();

        std::optional<Token> nextToken();

        static inline bool isDigitSep(const char c) { return c == '_'; }
    };
}

#endif // VIPER_FRAMEWORK_LEXER_LEXER_H