#pragma once
#include "__unified_forward.h"
#include "typechecker.h"
#include "compiler.h"
#include "lexer.h"
#include "parser.h"
#include "utility.h"
#include "error.h"
#include "interpreter.h"
#include "path.h"
#include "jakt__libc__io.h"
namespace Jakt {
namespace repl {
struct Editor {
  public:
FILE* standard_input_file;char* line_pointer;String prompt;static ErrorOr<repl::Editor> create(String const prompt);
void destroy();
Editor(FILE* a_standard_input_file, char* a_line_pointer, String a_prompt);

ErrorOr<repl::LineResult> get_line();
ErrorOr<String> debug_description() const;
};struct REPL {
  public:
NonnullRefPtr<compiler::Compiler> compiler;typechecker::Typechecker typechecker;types::ScopeId root_scope_id;NonnullRefPtr<interpreter::InterpreterScope> root_interpreter_scope;utility::FileId file_id;static ErrorOr<repl::REPL> create(path::Path const runtime_path, JaktInternal::Optional<String> const target_triple);
ErrorOr<void> run();
REPL(NonnullRefPtr<compiler::Compiler> a_compiler, typechecker::Typechecker a_typechecker, types::ScopeId a_root_scope_id, NonnullRefPtr<interpreter::InterpreterScope> a_root_interpreter_scope, utility::FileId a_file_id);

ErrorOr<bool> handle_possible_error();
ErrorOr<String> debug_description() const;
};namespace LineResult_Details {
struct Line{
String value;
template<typename _MemberT0>
Line(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Eof {
};
}
struct LineResult : public Variant<LineResult_Details::Line, LineResult_Details::Eof> {
using Variant<LineResult_Details::Line, LineResult_Details::Eof>::Variant;
    using Line = LineResult_Details::Line;
    using Eof = LineResult_Details::Eof;
ErrorOr<String> debug_description() const;
};
}
template<>struct Formatter<repl::Editor> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, repl::Editor const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<repl::REPL> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, repl::REPL const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
template<>struct Formatter<repl::LineResult> : Formatter<StringView>{
ErrorOr<void> format(FormatBuilder& builder, repl::LineResult const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));return format_error; }};
} // namespace Jakt
