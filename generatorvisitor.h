/*
    Copyright (C) 2009  Arno Rehn <arno@arnorehn.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef PARSERVISITOR_H
#define PARSERVISITOR_H

#include <QStringList>
#include <QStack>

#include <default_visitor.h>
#include <parsesession.h>
#include <lexer.h>

#include "type.h"

class NameCompiler;
class TypeCompiler;

class GeneratorVisitor : public DefaultVisitor
{
public:
    GeneratorVisitor(ParseSession *session);

protected:
    inline const Token& token(std::size_t token) { return m_session->token_stream->token(token); }
    QPair<bool, bool> parseCv(const ListNode<std::size_t> *cv);
    Class* resolveClassName(const QString& name);

    virtual void visitAccessSpecifier(AccessSpecifierAST* node);
    virtual void visitBaseSpecifier(BaseSpecifierAST* node);
    virtual void visitClassSpecifier(ClassSpecifierAST* node);
    virtual void visitDeclarator(DeclaratorAST* node);
    virtual void visitFunctionDefinition(FunctionDefinitionAST* node);
    virtual void visitNamespace(NamespaceAST* node);
    virtual void visitParameterDeclaration(ParameterDeclarationAST* node);
    virtual void visitPtrOperator(PtrOperatorAST* node);
    virtual void visitSimpleDeclaration(SimpleDeclarationAST* node);
    virtual void visitSimpleTypeSpecifier(SimpleTypeSpecifierAST* node);
    virtual void visitTemplateDeclaration(TemplateDeclarationAST* node);
    virtual void visitTypedef(TypedefAST* node);
    virtual void visitUsing(UsingAST* node);
    virtual void visitUsingDirective(UsingDirectiveAST* node);

private:
    NameCompiler *nc;
    TypeCompiler *tc;
    
    ParseSession *m_session;
    
    bool createType;
    short inClass;
    
    QVector<bool> *pointerDepth;
    bool *isRef;
    
    Type currentType;
    Type* currentTypeRef;
    Class::Kind kind;
    QStack<Class*> klass;
    QStack<Access> access;
    
    QStack<QStringList> usingTypes;
    QStack<QStringList> usingNamespaces;
    
    QStringList nspace;
};

#endif // PARSERVISITOR_H
