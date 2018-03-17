#include <LibGiac/LibGiac.h>
#include "MathCore.h"
#include "Parser.h"

namespace MathCore {
	

Node Eliminate(Node list, Node var) {
	String giac_cmd = "eliminate(" + list.AsInlineString() + "," + var.AsDataInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    Node out = ParseExpression(g.print(0).c_str());
    if (out.IsArray() && out.GetCount() == 1) out = out[0];
    return out;
}

Node Solve(Node n) {
	String giac_cmd = "solve(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    Node out = ParseExpression(g.print(0).c_str());
    if (out.IsArray() && out.GetCount() == 1) out = out[0];
    return out;
}

Node SolveComplex(Node n) {
	String giac_cmd = "csolve(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    Node out = ParseExpression(g.print(0).c_str());
    if (out.IsArray() && out.GetCount() == 1) out = out[0];
    return out;
}

Node FSolve(Node n) {
	String giac_cmd = "fsolve(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    Node out = ParseExpression(g.print(0).c_str());
    if (out.IsArray() && out.GetCount() == 1) out = out[0];
    return out;
}

Node SolveVar(Node expr, Node key) {
	String giac_cmd = "solve(" + expr.AsInlineString() + ", " + key.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
	g=giac::protecteval(g,1,0);
    Node out = ParseExpression(g.print(0).c_str());
    if (out.IsArray() && out.GetCount() == 1) out = out[0];
    return out;
}

Node SolveComplexVar(Node expr, Node key) {
	String giac_cmd = "csolve(" + expr.AsInlineString() + ", " + key.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    Node out = ParseExpression(g.print(0).c_str());
    if (out.IsArray() && out.GetCount() == 1) out = out[0];
    return out;
}

Node FSolveVar(Node expr, Node key) {
	String giac_cmd = "fsolve(" + expr.AsInlineString() + ", " + key.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    Node out = ParseExpression(g.print(0).c_str());
    if (out.IsArray() && out.GetCount() == 1) out = out[0];
    return out;
}

Node SimplifySum(Node expr, Node key, Node min, Node max) {
	String giac_cmd = "sum(" + expr.AsInlineString() + ", " + key.AsInlineString() + ", " + min.AsInlineString() + ", " + max.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node Simplify(Node n) {
	String giac_cmd = "simplify(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node TypeSimplify(Node n) {
	String giac_cmd = "usimplify(" + n.AsInlineString() + ")";
	LOG(giac_cmd);
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    LOG(g.print(0).c_str());
    return ParseExpression(g.print(0).c_str());
}

Node Integrate(Node n) {
	String giac_cmd = "integrate(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node Integrate(Node expr, Node min, Node max) {
	Node tmp = expr;//TODO: skip this
	Node var = FindVar(tmp);
	if (var.IsNull()) var = id("x");
	String giac_cmd = "integrate(" + expr.AsInlineString() + ", " + var.AsInlineString() + ", " + min.AsInlineString() + ", " + max.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node Integrate(Node expr, Node key) {
	String giac_cmd = "integrate(" + expr.AsInlineString() + ", " + key.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node Integrate(Node expr, Node key, Node min, Node max) {
	String giac_cmd = "integrate(" + expr.AsInlineString() + ", " + key.AsInlineString() + ", " + min.AsInlineString() + ", " + max.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    LOG(g.print(0).c_str());
    return ParseExpression(g.print(0).c_str());
}

Node Floating(Node n) {
	if (n.IsFuncIntegrate() || n.IsFuncDerive()) {
		LOG("Warning: preventing float from integrate or derive functions");
		return Int(0);
	}
	String giac_cmd = "float(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    // TODO: FIX: WHY XCAS SOMETIMES STARTS TO PRINT , INSTEAD OF . ???
    String hotfix = g.print(0).c_str();
    hotfix.Replace(",",".");
    return ParseExpression(hotfix);
    //return ParseExpression(g.print(0).c_str());
}

Node FindMin(Node expr, Node var) {
	String giac_cmd = "fMin(" + expr.AsInlineString() + ", " + var.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node FindMax(Node expr, Node var) {
	String giac_cmd = "fMax(" + expr.AsInlineString() + ", " + var.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node Limit(Node expr, Node key, Node closing) {
	String giac_cmd = "limit(" + expr.AsInlineString() + ", " + key.AsInlineString() + ", " + closing.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node LimitSimplify(Node expr, Node key, Node closing) {
	String giac_cmd = "limit(simplify(" + expr.AsInlineString() + "), " + key.AsInlineString() + ", " + closing.AsInlineString() + ")";
	//LOG(giac_cmd);
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node LinearSolve(Node expr_list, Node key_list) {
	String giac_cmd = "linsolve(" + expr_list.AsInlineString() + ", " + key_list.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}





Node GetVectorSpaceVector(Node space, Node vec) {
	int a = space.GetCount();
	int b = vec.GetCount();
	if (a != b) return Void();
	for(int i = 0; i < a; i++)
		if (space[i].GetCount() != b)
			return Void();
	
	Node lin_set = LinearSet();
	
	String giac_cmd = "linsolve( [";
	int c1 = space.GetCount();
	int chr = (a <= 3 ? 'x' : 'a');
	for(int i = 0; i < c1; i++) {
		if (i) giac_cmd += ", ";
		Node tmp;
		for(int j = 0; j < a; j++)
			tmp = Add(tmp, Multiply(id(ChrStr(chr+j)), space[j][i]));
		tmp = tmp == vec[i];
		lin_set.Add(tmp);
		giac_cmd += tmp.AsInlineString();
	}
	
	giac_cmd += " ], [";
	if (c1 <= 3) {for(int i = 0; i < c1; i++) {if (i) giac_cmd.Cat(','); giac_cmd.Cat('x'+i);}}
	else         {for(int i = 0; i < c1; i++) {if (i) giac_cmd.Cat(','); giac_cmd.Cat('a'+i);}}
	giac_cmd += "])";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g = giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}




Node AngleVecs(Node vec0, Node vec1) {
	Node theory = Cos(id("Q")) == (id("v_0") * id("v_1"))/(Length(id("v_0"))*Length(id("v_1")));
	if (vec0.GetCount() != vec1.GetCount()) return Void();
	String giac_cmd = "arccos((" + VectorMultiply(vec0, vec1).AsInlineString() + ")/(" + VectorLength(vec0).AsInlineString() + "*" + VectorLength(vec1).AsInlineString() + "))";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g = giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node SimplifyVector(Node vec) {
	int c1 = vec.GetCount();
	Node out = Array();
	for(int i = 0; i < c1; i++) {
		String giac_cmd = "simplify(";
		giac_cmd +=  vec[i].AsInlineString();
		giac_cmd += ")";
		giac::gen g(giac_cmd.Begin(),0);
		if (is_zero(g)) return Void();
	    g = giac::protecteval(g,1,0);
		out.Add( ParseGiacExpression(g.print(0).c_str()) );
    }
	return out;
}

	
Node Solve2(Node expr0, Node expr1, Node key0, Node key1) {
	String find = key0.AsInlineString() + "," + key1.AsInlineString();
	String giac_cmd = "solve( [";
	giac_cmd += expr0.AsInlineString() + ", " + expr1.AsInlineString() + "] ";
	giac_cmd += ", [" + find + "])";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g = giac::protecteval(g,1,0);
    return ParseGiacExpression(g.print(0).c_str());
}


Node GetVectorCrossVectors(Node vec0, Node vec1) {
	if (vec0.GetCount() != vec1.GetCount()) return Void();
	String giac_cmd = "cross(" + vec0.AsInlineString() + ", " + vec1.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g = giac::protecteval(g,1,0);
    return ParseGiacExpression(g.print(0).c_str());
}

Node SolveVector2(Node vec0, Node vec1, Node key0, Node key1) {
	if (vec0.GetCount() != vec1.GetCount()) return Void();
	String find = key0.AsInlineString() + "," + key1.AsInlineString();
	int c1 = vec0.GetCount();
	String giac_cmd = "solve([";
	for(int i = 0; i < c1; i++) {
		if (i) giac_cmd += ", ";
		giac_cmd += vec0[i].AsInlineString() + "=" + vec1[i].AsInlineString();
	}
	giac_cmd += "], [" + find + "])";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseGiacExpression(g.print(0).c_str());
}


Node LinePoint(Node line, Node point) {
	if (line.GetCount() != point.GetCount()*2) return Void();
	Node find = GetUnusedId(line, point);
	int c1 =  point.GetCount();
	String giac_cmd = "solve([";
	for(int i = 0; i < c1; i++) {
		if (i) giac_cmd += ", ";
		giac_cmd += GetElement(line, i, find).AsInlineString() + "=" + point[i].AsInlineString();
	}
	giac_cmd += "], [" + find.AsInlineString() + "])";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseGiacExpression(g.print(0).c_str());
}


Node LineCross(Node line0, Node line1, Node key0, Node key1) {
	if (line0.GetCount() != line1.GetCount()) return Void();
	String find = key0.AsInlineString() + "," + key1.AsInlineString();
	int c1 =  line0.GetCount();
	String giac_cmd = "solve([";
	for(int i = 0; i < c1; i++) {
		if (i) giac_cmd += ", ";
		giac_cmd += GetElement(line0, i, key0).AsInlineString(); + "=" + GetElement(line1, i, key1).AsInlineString();;
	}
	giac_cmd += "], [" + find + "])";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseGiacExpression(g.print(0).c_str());
}

Node Ellipse(Node n) {
	String giac_cmd = "ellipse(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) {return Void();}
    g=giac::protecteval(g,1,0);
    return ParseGiacExpression(g.print(0).c_str());
}

Node Hyperbola(Node n) {
	String giac_cmd = "hyperbola(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) {return Void();}
    g=giac::protecteval(g,1,0);
    return ParseGiacExpression(g.print(0).c_str());
}

Node Parabola(Node n) {
	String giac_cmd = "parabola(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) {return Void();}
    g = giac::protecteval(g,1,0);
    return ParseGiacExpression(g.print(0).c_str());
}

Node Derive(Node n) {
	String giac_cmd = "derive(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node Derive(Node n, Node key) {
	String giac_cmd = "derive(" + n.AsInlineString() + "," + key.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node DeriveFunction(Node n) {
	if (n.IsArray()) {
		Node out = Array();
		for(int i = 0; i < n.GetCount(); i++)
			out.Add(DeriveFunction(n[i]));
		return out;
	}
	
	Node out = n;
	if (!IsExprFunc(n)) return out;
	
	Node key = out[0];
	while (key.GetCount())
		key = key[0];
	
	if (out[1].IsArray()) {
		for(int i = 0; i < out[1].GetCount(); i++) {
			out[1][i].Derive(key);
		}
	} else {
		out[1].Derive(key);
	}
	
	out[0] = FunctionDerive(out[0]);
	
	
	return out;
}

Node DeriveFunction(Node n, Node key) {
	Node out = n;
	if (!IsExprFunc(n)) return out;
	
	out[0] = FunctionDerive(out[0]);
	out[1].Derive(key);
	
	return out;
}

Node DeriveCurve(Node n) {
	if (n.IsArray()) {
		Node out = Array();
		for(int i = 0; i < n.GetCount(); i++)
			out.Add(DeriveCurve(n[i]));
		return out;
	}
	
	Node out = n;
	if (!n.IsOp(OP_EQ)) return out;
	
	Node key = FindVar(out[1]);
	
	if (!key.IsId()) return out;
	
	if (out[1].IsArray()) {
		for(int i = 0; i < out[1].GetCount(); i++) {
			out[1][i].Derive(key);
		}
	} else {
		out[1].Derive(key);
	}
	
	out[0] = FunctionDerive(out[0]);
	return out;
}




Node Evaluate(Node n) {
	String giac_cmd = n.AsInlineString();
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

bool Test(Node n) {
	Node test = Op(OP_ISEQ).Add( Parenthesis().Add(n) ).Add(id("true"));
	Node ans = Evaluate(test);
	if (ans.Compare( id("true") ) == 0 )
		return true;
	return false;
}

bool TestEqual(Node in0, Node in1) {
	Node test = Op(OP_ISEQ).Add(in0).Add(in1);
	Node ans = Evaluate(test);
	if (ans.Compare( id("true") ) == 0 )
		return true;
	return false;
}

bool IsFunctionIncreasing(Node n) {
	if (!IsExprFunc(n))
		return false;
	Node der = DeriveFunction(n);
	Node test = der[1] > 0;
	Node ans = Evaluate(test);
	if (ans.Compare(id("true")) == 0) {
		return true;
	}
	
	return false;
}

Node ATan2(Node x, Node y) {
	if (Test(x > 0)) {
		return Function("atan").Add(y / x);
	}
	else if (Test(x < 0)) {
		if (Test(y >= 0))
			return Function("atan").Add(y / x) + Pi();
		else
			return Function("atan").Add(y / x) - Pi();
	}
	else {
		if (Test(y > 0))
			return Pi() / 2;
		else if (Test(y < 0))
			return Pi() / -2;
		else
			return Void();
	}
}

Node PartialFractionDecomposition(Node n) {
	String giac_cmd = "partfrac(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node PartialFractionDecomposition(Node n, Node key) {
	String giac_cmd = "partfrac(" + n.AsInlineString() + "," + key.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}


Node Factor(Node n) {
	String giac_cmd = "factor(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node Sum(Node expr, Node var, Node begin, Node end) {
	String giac_cmd = "sum(" + expr.AsInlineString() + "," + var.AsInlineString() + "," + begin.AsInlineString() + "," + end.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}


Node Real(Node n) {
	String giac_cmd = "real(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}


Node Imag(Node n) {
	String giac_cmd = "imag(" + n.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}


Node ExpTrig(Node exp) {
	String giac_cmd = "exp2trig(" + exp.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node SolveDifferentialEquation(Node expr, Node var) {
	String giac_cmd = "desolve(" + expr.AsInlineString() + "," + var.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node LaplaceTransform(Node expr, Node var) {
	String giac_cmd = "laplace(" + expr.AsInlineString() + "," + var.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node LaplaceTransform(Node expr, Node var, Node result_var) {
	String giac_cmd = "laplace(" + expr.AsInlineString() + "," + var.AsInlineString() + "," + result_var.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node LaplaceTransformInversed(Node expr, Node var) {
	String giac_cmd = "ilaplace(" + expr.AsInlineString() + "," + var.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

Node LaplaceTransformInversed(Node expr, Node var, Node result_var) {
	String giac_cmd = "ilaplace(" + expr.AsInlineString() + "," + var.AsInlineString() + "," + result_var.AsInlineString() + ")";
	giac::gen g(giac_cmd.Begin(),0);
	if (is_zero(g)) return Void();
    g=giac::protecteval(g,1,0);
    return ParseExpression(g.print(0).c_str());
}

}