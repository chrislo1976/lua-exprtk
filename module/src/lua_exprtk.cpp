
#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

#include "exprtk.hpp"

using namespace exprtk;


namespace lua_module
{

typedef symbol_table<double> symbol_table_t;
typedef expression<double>   expression_t;
typedef parser<double>       parser_t;


// helper struct for keeping double values and provide references to exprtk
// lua does not 'know' references to simple data types
struct variable_map
{
public:

    void insert(const std::string& name)
    {
        set(name, 0.0);
    }

    void set(const std::string& name, double value)
    {
        map[name] = value;
    }

    std::map<std::string,double> map;
};


sol::table open_module(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();


    // usertype 'variable_map' with methods
    module.new_usertype<variable_map>("variable_map", sol::constructors<variable_map()>()
        ,"insert", &variable_map::insert
        ,"set", &variable_map::set
    );


    // usertype 'symbol_table' with methods
    module.new_usertype<symbol_table_t>("symbol_table", sol::constructors<symbol_table_t()>()

        ,"add_variables",
            [](symbol_table_t& st, variable_map& map)
            {
                for (auto& [name, val] : map.map)
                {
                    st.add_variable(name, val, false);
                }
            }

        ,"add_constant", &symbol_table_t::add_constant
        ,"add_constants", &symbol_table_t::add_constants
    );


    // usertype 'expression' with methods
    module.new_usertype<expression_t>("expression", sol::constructors<expression_t()>()
        ,"register_symbol_table", &expression_t::register_symbol_table
        ,"value", &expression_t::value
    );


    // usertype 'parser' with methods
    module.new_usertype<parser_t>("parser", sol::constructors<parser_t()>()

        ,"compile",
            [](parser_t& p, const std::string& str, expression_t& expr)
            {
                bool success = p.compile(str, expr);
                return std::tuple<bool,std::string>(success, p.error());
            }

        ,"error_count", &parser_t::error_count
        ,"error", &parser_t::error
        ,"get_error", &parser_t::get_error
    );


    return module;
}

} // namespace lua_module


extern "C" int luaopen_exprtk(lua_State* L)
{
    return sol::stack::call_lua(L, 1, lua_module::open_module);
}
