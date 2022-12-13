#pragma once

#include <iostream>
#include <any>
#include <memory>
#include <string>

#include "Expr.h"
#include "RuntimeError.hpp"

class Interpreter : public ExprVisitor {

public:

	void interpret(std::shared_ptr<Expr> expr) {
		try {
			std::any value = evaluate(expression);
			std::cout << stringify(value) << std::endl;
		}
		catch (RuntimeError err) {
			runtimeError(error);
		}
	}

	std::any visitLiteralExpr(
		std::shared_ptr<Literal> expr) override {
		return expr->value;
	}

	std::any visitBinaryExpr(
		std::shared_ptr<Binary> expr) override {

		std::any left = evaluate(expr->left);
		std::any right = evaluate(expr->right);


		switch (expr->op.getTokenType()) {
			case BANG_EQUAL:
				return !isEqual(left, right);
			case EQUAL_EQUAL:
				return isEqual(left, right);
			case GREATER:
				checkNumberOperands(expr->op, left, right);
				return std::any_cast<double>(left) >
					std::any_cast<double>(right);
			case GREATER_EQUAL:
				checkNumberOperands(expr->op, left, right);
				return std::any_cast<double>(left) >=
					std::any_cast<double>(right);
			case LESS:
				checkNumberOperands(expr->op, left, right);
				return std::any_cast<double>(left) <
					std::any_cast<double>(right);
			case LESS_EQUAL:
				checkNumberOperands(expr->op, left, right);
				return std::any_cast<double>(left) <=
					std::any_cast<double>(right);
			case MINUS:
				checkNumberOperands(expr->op, left, right);
				return std::any_cast<double>left -
					std::any_cast<double>right;
			case PLUS:
				if (left.type() == typeid(double) &&
					right.type() == typeid(double))
					return std::any_cast<double>(left) +
					std::any_cast<double>(right);

				if (left.type() == typeid(std::string) &&
					right.type() == typeid(std::string))
					return std::any_cast<std::string>(left) +
					std::any_cast<std::string>(right);
				//break;
				RunTimeError{
					expr->op,
					"Operands must be two"
					"numbers or two strings." };
			case SLASH:
				checkNumberOperands(expr->op, left, right);
				return std::any_cast<double>left / 
					std::any_cast<double>right;
			case STAR:
				checkNumberOperands(expr->op, left, right);
				return std::any_cast<double>left * 
					std::any_cast<double>right;
		}

		// Unreachable
		return {};

	};
	
	std::any visitGroupingExpr(
		std::shared_ptr<Grouping>expr) override {
		return evaluate(expr->expression);
	};

	std::any visitUnaryExpr(
		std::shared_ptr<Unary>expr) override {
		std::any right = evaluate(expr->right);
		
		switch (expr->op.getTokenType) {
			case MINUS:
				checkNumberOperand(expr->op, right);
				return -std::any_cast<double>(right);
			case BANG:
				return !isTruthy(right);
		}


		/*unreachable*/
		return NULL;

	};

private:
	std::any evaluate(std::shared_ptr<Expr> expr) {
		/*summary: helper method; sends the expression
		back to interpreter's visitor implementation*/
		return expr->accept(*this);
	}

	bool isTruthy(const std::any& object) {
		if (object.type() == typeid(nullptr)) return false;
		if (object.type() == typeid(bool)) {
			return std::any_cast<bool>(object)
		}
		return true;
	}

	bool isEqual(const std::any& a, const std::any& b) {
		if (a.type() == typeid(nullptr) 
			&& b.type() == typeid(nullptr)) {
			return true;
		}
		if (a.type() == typeid(nullptr)) return false;
	}

	void checkNumberOperand(
		const Token& op, const std::any& left,
		const std::any& right) {
		if (left.type() == typeid(double) &&
			(right.type() == typeid(double))) {
			return;
		}
		throw RunTimeError{ op, "Operands must be a number." };
	}

	void checkNumberOperands(
		const Token& op, const std : any & left,
		const std::any& right) {
		if ((left.type() == typeid(double)) 
			&& (right.type() == typeid(double)) return;
		throw RunTimeError{op, "Operands must be numbers."};
	}

	std::string stringify(
		const std::any& object) {
	
	if (object.type() == typeid(nullptr)) return "nil";

	if (object.type() == typeid(double)) {
		std::string text = std::to_string(
			std::any_cast<double>(object)
		);

		if ((text[text.length() - 2] == '.')
			&& (text[text.length() - 1] == '0')) {
			text = text.substr(0, text.length() - 2);
		}
		return text;
	}

	}

};