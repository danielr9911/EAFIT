# coding: utf-8
require 'ast'
require 'scanner'
require 'token'
require 'calcex'

class Parser
  def initialize(istream)
    @scan = Scanner.new(istream)
  end
   
  def parse()
    return Prog()
  end
  
  private
  def Prog()
    result = Expr()
    #t = @scan.getToken
    
    #if t.type != :eof then
    #  print "Expected EOF. Found ", t.type, ".\n"
    #  raise ParseError.new
    #end
    
   return result
  end
  
  def Expr() 
    RestExpr(Term())
  end
   
  def RestExpr(e) 
    t = @scan.getToken
    
    if t.type == :add then
      return RestExpr(AddNode.new(e,Term()))
    end
    
    if t.type == :sub then
      return RestExpr(SubNode.new(e,Term()))
    end
      
    @scan.putBackToken()
    return e 
  end
  
  def Term()
    RestTerm(Storable())
  end

    
  def RestTerm(e)

    t = @scan.getToken
    if t.type == :times then
      return RestTerm(TimesNode.new(e,Storable()))
    end
    
    if t.type == :divide then
      return RestTerm(DivideNode.new(e,Storable()))
    end
    #Agregado caso modulo
    if t.type == :mod then
      return RestTerm(ModNode.new(e,Storable()))
    end
    
    @scan.putBackToken()
    return e
  end
   
  def Storable()
    MemOperation(Factor())    
  end

  def MemOperation(result)
    t = @scan.getToken

    if t.type == :keyword then
      if t.lex == 'S' then
        return StoreNode.new(result)
      end
      if t.lex == 'P' then
        return PlusNode.new(result)
      end
      if t.lex == 'M' then
        return MinusNode.new(result)
      end
      puts "Expected S, found: #{t.lex} at line #{t.line}, col: #{t.col}"
      raise ParseError.new
    end

    @scan.putBackToken()

    return result
  end
    
  def Factor() 

    t = @scan.getToken
    if t.type == :number then
      return NumNode.new(t.lex.to_i)
    end

    if t.type == :identifier then
      @scan.putBackToken
      return Assignable()
    end
    
    if t.type == :keyword then
      if t.lex == 'R' then
        return RecallNode.new
      elsif t.lex == 'C' then
        return ClearNode.new
      end
      puts "Expected R, found #{t.lex} at line: #{t.line}, col: #{t.col}"
      r
      aise ParseError.new
    end

    if t.type == :lparen then
      result = Expr()
      t = @scan.getToken
      if t.type == :rparen then
        return result
      end

      puts "Parser Error: expected ) found: #{t.lex}, at line: #{t.line}, col: #{t.col}"
      raise ParseError.new
    end

    puts "Parser Error: expected number, R or ( found: #{t.lex}, at line: #{t.line}, col: #{t.col}"
    raise ParseError.new
  end
  
  def Assignable()
    t=@scan.getToken
    return Assign(t.lex)
  end

  def Assign(str)
    t=@scan.getToken
    if t.type == :equ
      return AssignNode.new(str, Expr())
    end
    @scan.putBackToken
    return IdNode.new(str)
  end
end
