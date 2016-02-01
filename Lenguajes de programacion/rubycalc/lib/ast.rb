require 'set'

class BinaryNode
  attr_reader :left, :right
  
  def initialize(left,right)
    @left = left
    @right = right
  end
end
   
class UnaryNode
  attr_reader :subTree
   
  def initialize(subTree)
    @subTree = subTree
  end
end

class AddNode < BinaryNode
  def initialize(left, right)
    super(left,right)
  end
   
  def evaluate() 
    return @left.evaluate().to_i + @right.evaluate().to_i
  end
end

class SubNode < BinaryNode
  def initialize(left, right)
    super(left,right)
  end
   
  def evaluate() 
    return @left.evaluate().to_i - @right.evaluate().to_i
  end
end

class TimesNode < BinaryNode
  def initialize(left, right)
    super(left,right)
  end
   
  def evaluate() 
    return @left.evaluate().to_i * @right.evaluate().to_i
  end
end

class DivideNode < BinaryNode
  def initialize(left, right)
    super(left,right)
  end
   
  def evaluate() 
    return @left.evaluate().to_i / @right.evaluate().to_i
  end
end

#Se creo el nodo para modulo
class ModNode < BinaryNode
  def initialize(left, right)
    super(left, right)
  end
  
  def evaluate()
    return @left.evaluate().to_i % @right.evaluate().to_i
  end
end

class StoreNode < UnaryNode
  def initialize(subTree)
    super(subTree)
  end

  def evaluate()
    $calc.memory = subTree.evaluate.to_i
  end
end

class PlusNode < UnaryNode
  def initialize(subTree)
    super(subTree)
  end
  
  def evaluate()
    val = subTree.evaluate.to_i
    $calc.memory += val
  end
end

class MinusNode < UnaryNode
  def initilize(subTree)
    super(subTree)
  end
  
  def evaluate()
    val = subTree.evaluate.to_i
    $calc.memory -= val
  end
end

class NumNode 
  def initialize(num)
    @num = num
  end
   
  def evaluate() 
    return @num
  end
end

class RecallNode
   def evaluate()
     return $calc.memory.to_i
   end
end

class ClearNode
  def evaluate()
    $calc.memory = 0
    $calc.memory2.clear
    return 0
  end
end

class AssignNode < UnaryNode
  def initialize(str,subTree)
    super(subTree)
    @id=str
  end

  def evaluate()
    value = subTree.evaluate.to_i
    $calc.assign(@id,value)
    return value.to_i
  end
end

class IdNode
  def initialize(str)
    @id=str
  end

  def evaluate()
    $calc.memory2[@id].to_i
  end
end
