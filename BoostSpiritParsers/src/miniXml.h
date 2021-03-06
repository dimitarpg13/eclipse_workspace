#pragma once

// a mini XML-like parser
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace client
{
  namespace fusion = boost::fusion;
  namespace phoenix = boost::phoenix;
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;

  // our mini XML tree representation
  struct mini_xml;

  typedef
		  boost::variant<
		  	  boost::recursive_wrapper<mini_xml>
  	  	  	  , std::string
  	  	  	  >
  	  	  mini_xml_node;

  struct mini_xml
  {
	  std::string name;   // tag name
	  std::vector<mini_xml_node> children;
  };

}

// register our mini_xml struct with boost
BOOST_FUSION_ADAPT_STRUCT(
  client::mini_xml,
  (std::string, name)
  (std::vector<client::mini_xml_node>, children)
)

namespace client
{

	// print out the mini xml tree
	int const tabsize = 4;

	void tab(int indent);

	struct mini_xml_printer
	{
		mini_xml_printer(int indent = 0)
		  : indent(indent)
		{

		}

		void operator()(mini_xml const & xml) const;

		int indent;
	};

	struct mini_xml_node_printer : boost::static_visitor<>
	{
		mini_xml_node_printer(int indent = 0)
				: indent(indent)
		{
		}

		void operator()(mini_xml const & xml) const
		{
			mini_xml_printer(indent+tabsize)(xml);
		}

		void operator()(std::string const & text) const
		{
			tab(indent+tabsize);
			std::cout << "text: \"" << text << '"' << std::endl;
		}

		int indent;
	};


	// mini XML grammar definition
	template <typename Iterator>
	struct mini_xml_grammar :
			qi::grammar<Iterator, mini_xml(), qi::locals<std::string>, ascii::space_type>
	{
		mini_xml_grammar()
				: mini_xml_grammar::base_type(xml,"xml")
		{
			using qi::lit;
			using qi::lexeme;
			using qi::on_error;
			using qi::fail;
			using ascii::char_;
			using ascii::string;
			using namespace qi::labels;

			using phoenix::construct;
			using phoenix::val;

			text %= lexeme[+(char_ - '<')];
			node %= xml | text;

			start_tag %=
					'<'
				>> !lit('/')
				>	lexeme[+(char_ - '>')]
				> '>'
			;

			end_tag =
					"</"
				>  string(_r1)
				>  '>'
			;

			xml %=
					start_tag[_a = _1]
				>	*node
				> 	end_tag(_a)
			;


			xml.name("xml");
			node.name("node");
			text.name("text");
			start_tag.name("start_tag");
			end_tag.name("end_tag");

			on_error<fail>
			(
				xml
				, std::cout
				   << val("Error! Expecting ")
				   << _4 // what failed?
				   << val(" here: \"")
				   << construct<std::string>(_3, _2) // iterators to error-pos, end
				   << val("\"")
				   << std::endl
			);
		}

		qi::rule<Iterator, mini_xml(), qi::locals<std::string>, ascii::space_type> xml;
		qi::rule<Iterator, mini_xml_node(), ascii::space_type> node;
		qi::rule<Iterator, std::string(), ascii::space_type> text;
		qi::rule<Iterator, std::string(), ascii::space_type> start_tag;
		qi::rule<Iterator, void(std::string), ascii::space_type> end_tag;
	};
    //]

	bool test_minixml(std::string filename);

}
