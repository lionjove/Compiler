#include "stdafx.h"

#define BOOST_TEST_MODULE mytests

#include <boost/test/included/unit_test.hpp>
#include "Stages/LexerStage.h"
#include "CompilerParts/ConfigReader.h"

Config TestConfig;

LexerStage lexerStage;

using namespace boost::unit_test;


BOOST_AUTO_TEST_CASE(myTestCase)
{
	ConfigReader reader;

	TestConfig = reader.ReadConfigFromArgv(framework::master_test_suite().argc, framework::master_test_suite().argv);

	lexerStage = LexerStage(TestConfig.ExecutionFolder);

	std::wstring testData = L"switcher";
	std::wstring expectedValue = L"{\"Tokens\":[{\"Type\":\"Identificator\",\"Value\":\"switcher\"},{\"Type\":\"Separator\",\"Value\":\"\"}]}";

	BOOST_TEST((lexerStage.DoStage(testData) == expectedValue));

	testData = L"let a = 1";
	expectedValue = L"{\"Tokens\":[{\"Type\":\"KeyWord\",\"Value\":\"let\"},{\"Type\":\"Separator\",\"Value\":\" \"},{\"Type\":\"Identificator\",\"Value\":\"a\"},{\"Type\":\"Separator\",\"Value\":\" \"},{\"Type\":\"Assignment\",\"Value\":\"=\"},{\"Type\":\"Separator\",\"Value\":\" \"},{\"Type\":\"DoubleLiteral\",\"Value\":\"1\"},{\"Type\":\"Separator\",\"Value\":\"\"}]}";

	BOOST_TEST((lexerStage.DoStage(testData) == expectedValue));

	testData = L"for(var i = 0; i < 100; i++){consoleLog(i);}";
	expectedValue = L"{\"Tokens\":[{\"Type\":\"KeyWord\",\"Value\":\"for\"},{\"Type\":\"Separator\",\"Value\":\"(\"},{\"Type\":\"KeyWord\",\"Value\":\"var\"},{\"Type\":\"Separator\",\"Value\":\" \"},{\"Type\":\"Identificator\",\"Value\":\"i\"},{\"Type\":\"Separator\",\"Value\":\" \"},{\"Type\":\"Assignment\",\"Value\":\"=\"},{\"Type\":\"Separator\",\"Value\":\" \"},{\"Type\":\"DoubleLiteral\",\"Value\":\"0\"},{\"Type\":\"Separator\",\"Value\":\";\"},{\"Type\":\"Identificator\",\"Value\":\"i\"},{\"Type\":\"Separator\",\"Value\":\" \"},{\"Type\":\"LogicOperator\",\"Value\":\"<\"},{\"Type\":\"Separator\",\"Value\":\" \"},{\"Type\":\"DoubleLiteral\",\"Value\":\"100\"},{\"Type\":\"Separator\",\"Value\":\";\"},{\"Type\":\"Identificator\",\"Value\":\"i\"},{\"Type\":\"UnaryOperator\",\"Value\":\"++\"},{\"Type\":\"Separator\",\"Value\":\")\"},{\"Type\":\"Separator\",\"Value\":\"{\"},{\"Type\":\"Identificator\",\"Value\":\"consoleLog\"},{\"Type\":\"Separator\",\"Value\":\"(\"},{\"Type\":\"Identificator\",\"Value\":\"i\"},{\"Type\":\"Separator\",\"Value\":\")\"},{\"Type\":\"Separator\",\"Value\":\";\"},{\"Type\":\"Separator\",\"Value\":\"}\"},{\"Type\":\"Separator\",\"Value\":\"\"}]}";

	BOOST_TEST((lexerStage.DoStage(testData) == expectedValue));
}
