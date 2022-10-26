/*Generates the Expr Class
Most of the code was obtained from the-lambda-way cpplox repository. 
I used his code as guide for mine. There some small changes because
he as used C++17 while I am using C++20. Also I have commented my code
bit more throughly for future references.


C++ does not allow virtual methods to be templated; 
we will be using std::any

*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>
#include <cstring>


std::string toLowerCase(std::string_view str) {
	std::string out;
	for (char c : str) {
		out.push_back(std::tolower(c));
	}
	return out;
}

std::vector<std::string_view> split(
	std::string_view src, std::string_view del) {
	/*splits the string*/
	std::vector<std::string_view> ret;

	std::string_view::size_type start = 0;
	std::string_view::size_type end = src.find(del);

	//std::cout << start << "|" << end << std::endl;

	while (end != std::string_view::npos) {
		ret.push_back(src.substr(start, end - start));
		start = end + del.length();
		end = src.find(del, start);
	}

	ret.push_back(src.substr(start, end - start));
	return ret;
}

std::string_view trim(std::string_view str) {
	/*summary: trim the whitespace from
	a given string*/

	auto isspace = [](auto c) { return std::isspace(c); };

	/*left trim and right trim using std::find_if_not*/

	auto start = std::find_if_not(str.begin(), str.end(), isspace);
	auto end = std::find_if_not(str.rbegin(), str.rend(),
		isspace).base();


	std::string_view t{ start.operator->(), std::string_view::size_type(end - start)};
	std::cout << "trimmed " << t;

	return { start.operator->(),
		std::string_view::size_type(end - start)};
}


/*Code Taken from the-lambda-way
	In C++ we cannot rely on garbage collection to clean up our pointer
	messes for us. Instead of having to worry about calling delete
	every time we're done with some heap memory, we can dump this job
	onto std::shared_ptr. This function lets us use a '*' in our
	metaprogram to indicate that we actually want a smart pointer.
*/
std::string fix_pointer(std::string_view field) {
	/**/
	std::ostringstream out;
	std::string_view type = split(field, " ")[0];
	std::string_view name = split(field, " ")[1];
	bool close_bracket = false;

	if (type.substr(0, 12) == "std::vector<") {
		out << "std::vector<";
		type = type.substr(12, type.length() - 13); // ignores closing '>'
		close_bracket = true;
	}

	if (type.back() == '*') {
		type.remove_suffix(1);
		out << "std::shared_ptr<" << type << ">";
	}
	else {
		out << type;
	}

	if (close_bracket) out << ">";
	out << " " << name;

	return out.str();
}

void defineVisitor(
	std::ofstream& writer, std::string_view baseName,
	const std::vector<std::string_view>& types) {

	/*struct ExprVisitor
	*/
	writer << "struct " << baseName << "Visitor {\n";

	/*virtual std::any visitBinaryExpr(
		std::shared_ptr<Binary> expr)= 0
	*/
	for (std::string_view type : types) {
		std::string_view typeName = trim(split(type, ":")[0]);
		writer << "	virtual std::any visit" << typeName << baseName <<
			"(std::shared_ptr<" << typeName << ">" 
			<< toLowerCase(baseName) << ") = 0;\n";
	}

	/*destructor
	virtual ~ExprVisitor() = default;
	*/
	writer << "	virtual ~" << baseName << "Visitor() = default;\n";
	writer << "};\n";
}


void defineType(
	std::ofstream& writer, std::string_view basename, 
	std::string_view className, std::string_view fieldList) {


	/*struct Binary: Expr, public std::enable_shared_from_this<Binary> {*/
	writer << "struct " << className << ": " << basename <<
		", public std::enable_shared_from_this<" << className << "> {\n";


	/*constructor  
	Binary(std::shared_ptr<Expr> left, Token op, 
	std::shared_ptr<Expr> right): left{std::move(left)}, 
	op{std::move(op)}, right{std::move(right)}*/
	writer << " " << className << "(";

	std::vector<std::string_view> fields = split(fieldList, ", ");
	writer << fix_pointer(fields[0]);

	for (int i = 1; i < fields.size(); ++i) {
		writer << ", " << fix_pointer(fields[i]);
	}

	writer << ")\n"
		<< "	: ";

	/*store parameters in the fields*/
	std::string_view name = split(fields[0], " ")[1];
	writer << name << "{std::move(" << name << ")}";

	for (int i = 1; i < fields.size(); ++i) {
		name = split(fields[i], " ")[1];
		writer << ", " << name << "{std::move(" << name << ")}";
	}

	writer << "\n"
		<< "	{}\n";

	/*visitor pattern*/
	writer << "\n"
		"	std::any accept(" << basename << "Visitor& visitor)"
		" override {\n"
		"	return visitor.visit" << className << basename <<
		"(shared_from_this());\n"
		"	}\n";


	/*fields*/
	writer << "\n";
	for (std::string_view field : fields) {
		writer << " const " << fix_pointer(field) << ";\n";
	}

	writer << "};\n\n";
}


void defineAst(
	const std::string& outputDir, const std::string& basename,
	const std::vector<std::string_view>& types) {

	std::string path = outputDir + "/" + basename + ".h";
	std::ofstream writer{ path };

	/*including the header files*/
	writer << "#pragma once\n"
		"\n"
		"#include <any>\n"
		"#include <memory>\n"
		"#include <utility>\n"
		"#include <vector>\n"
		"#include \"Token.h\"\n"
		"\n";

	/*forward declare classes
	struct Binary;
	*/
	for (std::string_view type : types) {
		std::string_view className = trim(split(type, ": ")[0]);
		writer << "struct " << className << ";\n";
	}

	writer << "\n";
	/*Visitor Classes*/
	defineVisitor(writer, basename, types);

	/*struct Expr{
		virtual std::any accept(ExprVisitor& visitor) = 0;
	}*/
	writer << "\n"
		"struct " << basename << " {\n"
		"	virtual std::any accept(" << basename <<
		"Visitor& visitor) =0;\n"
		"};\n\n";

	for (std::string_view type : types) {
		std::string_view className = trim(split(type, ": ")[0]);
		std::string_view fields = trim(split(type, ": ")[1]);
		defineType(writer, basename, className, fields);
	}

}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Usage: generate_ast <output directory>\n";
		std::exit(1);
	}

	std::string outputDir = argv[1];


	defineAst(outputDir, "Expr", {
		"Binary   : Expr* left, Token op, Expr* right",
		"Grouping : Expr* expression",
		"Literal  : std::any value",
		"Unary    : Token op, Expr* right"
	});
}