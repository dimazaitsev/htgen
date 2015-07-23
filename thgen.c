/* Generator of Petri net model of hypertorus grid - a hypercube with closed opposite edges */
/* Product of Dmitry Zaitsev member.acm.org/~daze */
/* USAGE: htgen d k p b > pn_model.net */
/* d - number of dimensions, k - size of hypertorus, p - number of packets in each buffer section, b - available buffer size */
/* output format - .net file of Tina www.laas.fr/tina */

#include <stdio.h>
#include <stdlib.h>

/* print the current cell index */
#define PUTINDX { for( u=1; u<=d; u++) printf( ".%d", i[u] ); }

/* print the next cell index */
#define PUTINDXNEXT( r ) { for( u=1; u<=d; u++) printf( ".%d", (u!=(r))? i[u] : (i[u]<k)? i[u]+1 : 1 ); }

/* the port buffer size */
#define IOBL 1

main( int argc, char * argv[] )
{
 int d, k, *i, j, u, v, dir, p, b;
 int loop, go;

 if( argc < 5 )
 {
   printf( "Generator of Petri net model of hypertorus grid -\n"
           "  a hypercube with closed opposite edges\n"
           "Product of Dmitry Zaitsev member.acm.org/~daze\n\n" 
           "USAGE: htgen d k p b > pn_model.net \n"
           "  d - number of dimensions, k - size of hypertorus,\n"
           "  p - number of packets in each buffer section, b - available buffer size\n"
           "  output format - .net file of Tina www.laas.fr/tina\n\n"
     );
   exit(2);
 }
 else { d = atoi( argv[1] ); k = atoi( argv[2] ); p = atoi( argv[3] ); b = atoi( argv[4] );}
 
 /* allocate the grid cell index i */
 i = (int *) malloc( (d+1)* sizeof( int ) );
 if( i == NULL )
 {
   printf( "*** not enough memory for i[]\n" );
   exit(2);
 }
 
 /* initialize index of the first grid node */
 for( j=1; j<=d; j++ ) i[j] = 1;

 loop=1;

 while( loop )
 {
   /* generate subnet for the current grid node */
   /* for on dimensions */
   for( j=1; j<=d; j++ )
   {
     /* direction 1 */
     /* output port */
     printf( "tr {to.d%d.n1", j );
     PUTINDX;
     printf( "} {pol.d%d.n1", j );
     PUTINDX;
     printf( "} {pb.d%d.n1", j );
     PUTINDX;
     printf( "} -> {po.d%d.n1", j );
     PUTINDX;
     printf( "} {pbl" );
     PUTINDX;
     printf( "}\n" );
     
     /* packets in the buffer section */
     printf("pl {pb.d%d.n1", j);
     PUTINDX;
     printf("} (%d)\n", p);
     
     /* port buffer size */
     printf("pl {pol.d%d.n1", j);
     PUTINDX;
     printf("} (%d)\n", IOBL);
     
     /* input port */
     for( v=1; v<=d; v++ )
       for( dir=1; dir<=2; dir++ )
	     if( (v!=j) || (dir!=1) )
	     {
	        printf( "tr {ti.d%d.n1.d%d.n%d", j, v, dir );
	        PUTINDX;
	        printf( "} {pi.d%d.n1", j );
	        PUTINDX;
	        printf( "} {pbl" );
	        PUTINDX;
	        printf( "} -> {pil.d%d.n1", j );
	        PUTINDX;
	        printf( "} {pb.d%d.n%d", v, dir );
	        PUTINDX;
	        printf( "}\n" );
	      } /* for v */
	 
     /* port buffer size */
     printf("pl {pil.d%d.n1", j);
     PUTINDX;
     printf("} (%d)\n", IOBL);

     /* direction 2 */

     /* output port */
     printf( "tr {to.d%d.n2", j );
     PUTINDX;
     printf( "} {pil.d%d.n1", j );
     PUTINDXNEXT( j );
     printf( "} {pb.d%d.n2", j );
     PUTINDX;
     printf( "} -> {pi.d%d.n1", j );
     PUTINDXNEXT( j );
     printf( "} {pbl" );
     PUTINDX;
     printf( "}\n" );
       
     /* packets in the buffer section */
     printf("pl {pb.d%d.n2", j);
     PUTINDX;
     printf("} (%d)\n", p);

     /* input port */
     for( v=1; v<=d; v++ )
	   for( dir=1; dir<=2; dir++ )
	     if( (v!=j) || (dir!=2) )
	     {
	       printf( "tr {ti.d%d.n2.d%d.n%d", j, v, dir );
	       PUTINDX;
	       printf( "} {po.d%d.n1", j );
	       PUTINDXNEXT( j );
	       printf( "} {pbl" );
	       PUTINDX;
	       printf( "} -> {pol.d%d.n1", j );
	       PUTINDXNEXT( j );
	       printf( "} {pb.d%d.n%d", v, dir );
	       PUTINDX;
	       printf( "}\n" );
         } /* for v */
     	         
   } /* for j (on dimensions) */
   
   /* available size of the internal buffer */
   printf("pl {pbl" );
   PUTINDX;
   printf("} (%d)\n", b);

   /* calculate indices of the next grid cell */
   go = 1;
   j=d;
   while( go )
   {
     (i[j])++;
     if( i[j] > k )
     {
       if( j == 1 ) { loop=0; go=0; }
       else
       {
	     i[j]=1;
	     j--;
       }
     }
     else go=0;
   } /* while go */
 } /* while loop */

 printf("net ht%dd%dk%dp%db\n", d, k, p, b);
 free( i );
} /* main */
