// Copyright (C) 2018 Christian T Preuss
// This file is part of Spectrum.
//
// Spectrum is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.  

#ifndef COLOURTOOLS_H
#define COLOURTOOLS_H

#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
#include<complex>
#include<cmath>
#include<climits>

using namespace std;

//*********************************************************************************************************
//
// Global Constants - TODO: put in Spectrum.h
//
//*********************************************************************************************************

const double NC(3.); // number of colours
const double TR(1./2.); // generator normalisation
const double CF(TR*(NC*NC-1)/NC); // Fundamental Casimir
const double CA(2.*TR*NC); // Adjoint Casimir

//*********************************************************************************************************
//
// Class process
//
//*********************************************************************************************************

class process {
  //incoming and outgoing legs: an index is assigned to each leg (first component) and the particle is stored in second component
  vector<pair<size_t,string>> m_in_legs;
  vector<pair<size_t,string>> m_out_legs;

 public:
  process();
  ~process();
  void add_in_leg(string ptcl);
        void add_out_leg(string ptcl);
        void delete_all_legs();
        size_t no_of_legs();
        string leg(size_t lno);
        bool is_in_leg(size_t lno);
};

//*********************************************************************************************************
// 
// Class ColourFactor
//
//*********************************************************************************************************

class ColourFactor {
  // Power of NC
  int m_NC;
  
  // Power of TR
  int m_TR;

  // Power of CF;
  int m_CF;

  // Power of CA;
  int m_CA;

  // Complex prefactor
  complex<double> m_cmplx;

  friend class ColourSum;

 public:
  // Default constructor
  ColourFactor();

  // Constructor from string
  ColourFactor(string expr);

  // Constructor from powers and cnumber
  ColourFactor(complex<double> cnum, int pow_NC, int pow_TR, int pow_CF, int pow_CA);
  
  // Getter for string representation
  string get_string();

  // Assignment with string
  void operator=(string expr);

  // Assignment with number;
  void operator=(complex<double> z);

  // Multiplication with a colour factor in terms of a string
  ColourFactor operator*(string expr);

  // Multiplication with a colour factor in terms of a string
  void operator*=(string expr);

  // Multiplication with another ColourFactor
  ColourFactor operator*(ColourFactor rhs);

  // Multiplication with another ColourFactor and assignment
  void operator*=(ColourFactor rhs);
  
  // Multiplication with a complex number
  ColourFactor operator*(complex<double> rhs);

  // Multiplication with a complex number and assignment
  void operator*=(complex<double> rhs);

  // Division by another ColourFactor
  ColourFactor operator/(ColourFactor rhs);
  
  // Division by another ColourFactor and assignment
  void operator/=(ColourFactor rhs);

  // Complex conjugate
  ColourFactor cconj();

  // Delete
  void del();

  // Replace CA by 2*TR*NC
  void replace_CA();

  // Replace CF by TR*NC (large-NC approximation)
  void replace_CF();

  // Replace TR by whatever value it was given
  void replace_TR();

  // Method to get order in NC
  int get_order_NC();

  // Method to get cnumber
  complex<double> get_cnum();

  // Method to get cnumber at leading colour
  complex<double> get_cnum_LC();

  // Method to get cnumber at large-NC
  complex<double> get_cnum_large_NC();

};

//*********************************************************************************************************
// 
// Class ColourSum
//
//*********************************************************************************************************

class ColourSum {
  // Sum of ColourFactors
  vector<ColourFactor> m_cf_sum;

 public:
  // Default constructor
  ColourSum();

  // Constructor from ColourFactor
  ColourSum(ColourFactor cf);

  // Constructor from expression as string
  ColourSum(string expr);

  // Getter for string representation
  string get_string();

  // Assignment with number
  void operator=(complex<double> z);

  // Assignment with string
  void operator=(string expr);

  // Method to add further colour factors as string
  ColourSum operator+(string expr);

  // Method to add further colour factors as string and assignment
  void operator+=(string expr);

  // Method to add another ColourFactor
  ColourSum operator+(ColourFactor rhs);

  // Method to add another ColourFactor and assignment
  void operator+=(ColourFactor rhs);

  // Method to add two ColourSums
  ColourSum operator+(ColourSum rhs);

  // Method to add two ColourSums and assignment
  void operator+=(ColourSum rhs);

  // Method to multiply two ColourSums
  ColourSum operator*(ColourSum rhs);

  // Method to multiply two ColourSums and assignment
  void operator*=(ColourSum rhs);

  // Method to multiply ColourSum with string expression
  ColourSum operator*(string expr);

  // Method to multiply ColourSum with string expression and assignment
  void operator*=(string expr);

  // Method to multiply with complex number
  ColourSum operator*(complex<double> z);

  // Method to multiply with complex number and assignment
  void operator*=(complex<double> z);

  // Complex conjugate
  ColourSum cconj();
  
  // Method to delete all terms
  void del();
  
  // Method to get leading-NC term
  ColourFactor get_leading_NC();

  // Method to get cnumber
  complex<double> get_cnum();

  // Method to get cnumber at leading colour
  complex<double> get_cnum_LC();

  // Method to get cnumber at large-NC
  complex<double> get_cnum_large_NC();
};

//*********************************************************************************************************
// 
// Class delta
//
//*********************************************************************************************************

class delta {
 public:
  // Adjoint/Fundamental indices i, j in k_[i,j]/K_[i,j]
  size_t m_i, m_j;

  // Are indices adjoint?
  bool m_adj;
  
  // Constructor from indices
  delta(size_t i, size_t j, bool adj);

  // Destructor
  ~delta();

  // Method to check whether given index is free
  bool is_free(size_t ind);

  //Method to build string representation
  string build_string();
};

//*********************************************************************************************************
//
// Class fundamental
//
//*********************************************************************************************************

class fundamental {
 public:
  // Adjoint index i and fundamental indices a, b in t_[i,a,b]      
  size_t m_i, m_a, m_b;

  // Constructor from indices
  fundamental(size_t i, size_t a, size_t b);

  // Destructor
  ~fundamental();
  
  // Method to check whether given index is free
  bool is_free(size_t ind);

  // Method to build string representation
  string build_string();
};

//*********************************************************************************************************
//
// Class antisymmetric
//
//*********************************************************************************************************

class antisymmetric {
 public:
  // Adjoint indices i, j, k in  f_[i,j,k]
  size_t m_i, m_j, m_k;

  // Constructor from indices
  antisymmetric(size_t i, size_t j, size_t k);

  // Destructor
  ~antisymmetric();

  // Method to check whether given index is free
  bool is_free(size_t ind);

  // Method to build string representation
  string build_string();
};

//*********************************************************************************************************
//
// Class symmetric
//
//*********************************************************************************************************

class symmetric {
 public:
  // Adjoint indices i, j, k in d_[i,j,k]
  size_t m_i, m_j, m_k;
  
  // Constructor from indices
  symmetric(size_t i, size_t j, size_t k);

  // Destructor
  ~symmetric();

  // Method to check whether given index is free
  bool is_free(size_t ind);

  // Method to build string representation
  string build_string();
};

//*********************************************************************************************************
//
// Class c_term
//
//*********************************************************************************************************

class c_term {
 private:
  // The prefactor of the colour term as a ColourSum
  ColourSum m_cnum;

  // The product of all Kronecker deltas (both fundamental and adjoint)
  vector<delta> m_k_vec;

  // The product of all fundamental generators
  vector<fundamental> m_t_vec;

  // The product of all antisymmetric structure constants
  vector<antisymmetric> m_f_vec;

  // The product of all symmetric structure constants
  vector<symmetric> m_d_vec;

  // Integer to store first free index 
  size_t m_fi;
    
  // Method to check whether colour term vanishes
  void replace_zero();

  // Method to replace quantities with adjoint indices
  bool replace_adjoint();

  // Method to replace Kronecker deltas (both fundamental and adjoint)
  void evaluate_deltas(bool to_LC = false);

  // Method to shift all indices by a constant
  void shift_inds(size_t by, bool all);
    
 public:
  // Default constructor
  c_term();

/*   // Constructor from given quantities */
/*   c_term(delta& k, fundamental& t, antisymmetric& f, symmetric& d, complex<double> c = complex<double>(0.,0.)); */

  // Constructor from given quantities
  c_term(delta& k, fundamental& t, antisymmetric& f, symmetric& d, ColourFactor c = ColourFactor());

  // Destructor
  ~c_term();
  
  // Method to multiply with another colour term (without checking for duplicate indices)
  void push_back(c_term ct);

  // Method to multiply with a Kronecker delta (without checking for duplicate indices)
  void push_back(delta k);

  // Method to multiply with a fundamental generator (without checking for duplicate indices)
  void push_back(fundamental t);

  // Method to multiply with an antisymmetric structure constant (without checking for duplicate indices)
  void push_back(antisymmetric f);

  // Method to multiply with a symmetric structure constant (without checking for duplicate indices)
  void push_back(symmetric d);

  // Method to set the prefactor
  void set_cnumber(ColourFactor c);
    
  // Method to contract all internal indices
  // (no replacements will be made that produce new terms)
  void simplify();

  // Method to get hermitian conjugate
  c_term hconj();

  // Method to multiply with another colour term (avoiding duplicate indices)
  c_term operator*(c_term ct);

  // Method to get result from index contraction
  ColourSum result();
  
  // Method to delete all quantities from colour term
  void clear();
    
  // Method to get string representation of colour term
  string build_string();

  // Method to print string representation to terminal
  void print();
  
  // Declare c_amplitude as friend class
  // (needed to alter c_terms)
  friend class c_amplitude;
};

//*********************************************************************************************************
//
// Class c_amplitude
//
//*********************************************************************************************************

class c_amplitude {
  // Sum of all colour terms
  vector<c_term> m_cterm_vec;
  
  // Result of index contraction in all terms 
  ColourSum m_result;
    
 public:
  // Default constructor
  c_amplitude();

  // Constructor from colour term
  c_amplitude(c_term ct);
  
  // Constructor from string representation of colour term
  c_amplitude(string expr);

  // Destructor
  ~c_amplitude();
  
  // Method to add another colour term
  void add(c_term ct);

  // Method to return hermitian conjugate of colour amplitude
  c_amplitude hconj();

  // Method to multiply by complex number
  c_amplitude operator*(complex<double> z);

  // Method to multiply with another colour amplitude (avoiding duplicate indices)
  c_amplitude operator*(c_amplitude ca);

  // Method to multiply with another colour amplitude (without check for duplicate indices)
  void multiply(c_amplitude ca);

  // Method to shift all indices by constant
  c_amplitude shift_to_internal(size_t by);

  // Method to calculate scalar product < c1 | c2 > of two colour amplitudes
  ColourSum scprod(c_amplitude ca, bool to_LC = false);

  // Method to delete all terms
  void clear();
  
  // Method to evaluate colour amplitude at leading colour order
  void evaluate_LC();

  // Method to evaluate colour amplitude at full colour
  void evaluate();

  // Method to simplify colour amplitude (calls c_term::simplify() for all terms)
  void simplify();

  // Method to get result of index contraction
  ColourSum result();
    
  // Method to get number of terms in colour amplitude
  size_t no_of_terms();

  // Method to build string representation of colour amplitude
  string build_string();

  // Method to print string representation to terminal
  void print();
};

#endif
