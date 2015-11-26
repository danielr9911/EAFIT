require 'parser'
require 'ast'

class Calculator
  attr_accessor :memory
  attr_accessor :memory2
  attr_accessor :assigns
  attr_accessor :countAssigns
  
  def initialize()
    @memory = 0
    @memory2 = Hash.new(0)
    @assigns = Hash.new(0)
    @countAssigns = 0
  end
  
  def eval(expr)
    parser = Parser.new(StringIO.new(expr))
    ast = parser.parse()
    return ast.evaluate()
  end

  def assign(id, value)
    @memory2[id]=value
    @assigns[@countAssigns]=(id+" <- "+value.to_s)
    @countAssigns+=1
  end
  
  def listAssigns() 
    list=""
    i=0
    while i<@countAssigns do
      list = list + @assigns[i]
      if(i!=(@countAssigns-1))
        list = list + ", "
      end
      i=i+1
    end
    return list
  end
  
end

