# lua-exprtk

[![License](http://img.shields.io/badge/License-MIT-brightgreen.svg)](LICENSE)

A lua wrapper for exprtk (C++ Mathematical Expression Parsing And Evaluation Library)

## Usage
```lua
local exprtk = require('lua-exprtk')

local varMap = exprtk.variable_map.new()
varMap:add('a')

local symbols = exprtk.symbol_table.new()
symbols:add_constants()
symbols:add_variables(varMap)

local expr = exprtk.expression.new()
expr:register_symbol_table(symbols)

local parser = exprtk.parser.new()

local success,err = parser:compile('clamp(-0.5,sin(a*pi/180),0.5)', expr)
if not success then
    print('Error during parsing:', err)
    return
end

for i=0,360 do
    varMap:set('a', i)
    print(i, expr:value())
end
```

For a full list of expressions, look [here](https://www.partow.net/programming/exprtk/index.html).

## External dependencies (included)
- [Sol3 (sol2 v3.0) - a C++ <-> Lua API wrapper with advanced features and top notch performance]( https://github.com/ThePhD/sol2 )
- [exprtk - C++ Mathematical Expression Parsing And Evaluation Library](https://github.com/ArashPartow/exprtk)
