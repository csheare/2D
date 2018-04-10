lude <i o s t r e am >
2 # inc lude <s t r i n g >
34
c l a s s A f
5 publ i c :
6 A( i n t n ) : number ( n ) f g
7 ˜A( ) f s t d : : c o u t << ” d e l e t i n g A” << s t d : : e n d l ; g
8 i n t getNumber ( ) c ons t f r e turn number ; g
9 v i r t u a l s t d : : s t r i n g getName ( ) c ons t f r e turn ” I ’m A” ; g
10 p r i v a t e :
11 i n t number ;
12 g ;
13
14 c l a s s B : publ i c A f
15 publ i c :
16 B( i n t m, i n t n ) : A(m) , number ( n ) f g
17 ˜B( ) f s t d : : c o u t << ” d e l e t i n g B” << s t d : : e n d l ; g
18 i n t getNumber ( ) c ons t f r e turn number ; g
19 v i r t u a l s t d : : s t r i n g getName ( ) c ons t f r e turn ” I ’m B” ; g
20 p r i v a t e :
21 i n t number ;
22 g ;
23
24 i n t main ( ) f
25 A x = new B( 1 2 , 1 3 ) ;
26 B y = new B( 6 6 , 7 7 ) ;
27 A z = new B( 1 , 2 ) ;
28 s t d : : c o u t << x􀀀>getNumber ( ) << s t d : : e n d l ;
29 s t d : : c o u t << x􀀀>getName ( ) << s t d : : e n d l ;
30 s t d : : c o u t << y􀀀>getNumber ( ) << s t d : : e n d l ;
31 s t d : : c o u t << y􀀀>getName ( ) << s t d : : e n d l ;
32 d e l e t e z
