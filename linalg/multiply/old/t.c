/* t.c - Travelling Salesman  */
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>

int d;				  	// d is size of input 
float *f1,*f2;				// hold x and y
float **f;				// holds the distances
float best_length = FLT_MAX;            // the length of the best path 
int *best_path ; 
int count_tours=0;

typedef struct s_node
{
	int level; 
	int *path;
	float bound;
}*t_node;

t_node 	give_birth();
t_node 	give_path(t_node parent, t_node kid);		
float 	get_bound(t_node n);
float 	get_length(t_node n);
float 	cmp_distances(float x1,float y1,float x2,float y2);
void 	get_distances(); 		
void 	get_paths(t_node n);
void 	get_best_path(t_node n);
void 	init();
int 	in_path(int vertex,t_node n);
int 	is_promising(t_node n);
int 	is_tour(t_node n);					

float cmp_distances(float x1,float y1,float x2,float y2) 
{
        float distance,x,y,xsquare,ysquare,sum; 
		x=(x2)-(x1);
		y=(y2)-(y1); 
		xsquare=pow(x,2);
		ysquare=pow(y,2); 
		sum=xsquare+ysquare; 
		distance=sqrt(sum); 
		return distance;
}
void get_distances() 		// perform distance formula on all 
{															// necessary points, store distances in **f.
	int i,j;
	for (i=1;i<=d;i++) 
	{
//		printf ("let's do %f %f\n",f1[i] , f2[i]) ;
		for (j=1;j<=d;j++) 
		{
			if (i == j)
			{
				//do nothing
			}
			else
			{
//				printf ("  let's do %f %f\n",f1[i] , f2[i]) ;
//				printf ("  and %f %f\n",f1[j] , f2[j]) ;
//				printf ("  the dist is %f\n",cmp_distances( f1[i], f2[i], f1[j], f2[j] )  );
				f[i][j]=cmp_distances( f1[i], f2[i], f1[j], f2[j] ) ;
			}
		}
	}
}
void init()
{
	int i,j;
	float x, y;
	scanf("%d",&d);					//get input //	printf ("d is %d\n",d);
	f1=(float *)malloc ((d)*sizeof(float));		//take care of arrays
	f2=(float *)malloc ((d)*sizeof(float));
	best_path=(int *)malloc ((d) * sizeof (int));		

	f=(float **) malloc ( d * sizeof (float *));
	for ( i=1 ; i<=d ; i++) 
	{
		f[i] = (float *)malloc(d*sizeof(float));
	}

	for (i=1;i<=d;i++)		                //get some more input
	{
		scanf("%f %f\n",&x,&y);
		f1[i] = x;
		f2[i] = y;
	}
	for ( i=1 ; i < d; i++ ) 
	{
		best_path[i] = 0 ;
	}
//	for (i=1;i<=d;i++) { 	printf("%d %f %f\n",i,f1[i],f2[i]) ; }	//echo input

}
t_node give_birth(t_node parent)
{
	t_node n;
	n=(t_node)malloc(sizeof(struct s_node));
	n->level = parent->level+1 ; 
//	printf ( "parentn->level = %d\n",parent->level ) ;
//	printf ( "n->level = %d\n",n->level ) ;
	n->bound = get_bound(n); 
	n->path =(int *)malloc ((d)*sizeof(int));
	return n;
}
int in_path(int node,t_node n)
{
	int i;
	for (i=1 ; i<=(n->level);  i++) 
	{
	if (node==n->path[i]) return 1;
	} 
	return 0;
}
t_node give_path(t_node parent, t_node kid)
{
	int i;
	for (i=1;i<=(parent->level);i++)
	{
		kid->path[i] = parent->path[i];
	}
	return (kid);
}
float get_length(t_node n)
{
	float l=0;

	int i;
	int A = n->path[1];					//dr delcher, i tidied up baji boo
	int B;

	for (i = 2; i <= n->level;  i ++)
	{
		B = n->path[i]; 	//	printf ("<B %d> ",B ) ;
		l += f[A][B];		// printf ("<lookup %f> ",f[A][B] ) ; printf ("<l %f> ",l ) ;
		A = B;				// printf ("<A %d> ",A ) ;
	}
	l+=f[A][1];   		// wrap around occurs here ...  
							//	printf ("<wrap %f> ",f[A][1] ) ; //printf ("<length %f> ",l);

//	printf("length->%f\n",l);
	return l;
}
void get_best_path(t_node n)
{
	int i;



	float length = get_length(n); //	printf ( "<length %f> ", l); //	printf ( "<best %f> ", b);

	//printf ("length =%f \n",length);
	//printf ("best_length =%f \n",best_length);

	if (length < best_length )
	{
		for (i=1 ; i <= d; i++ ) 
		{
			best_path[i]=n->path[i]; 		//printf  ( " %d",best_path[i]);
		}							 		//printf  ( ">");
		best_length=length ; //printf ( "<best %f> ", b); 	//printf  ( "<best path");
	}




}
int is_tour(t_node n)
{
	if (n->level == d ) return 1; else return 0 ;
}
int is_promising(t_node n)
{

	if ( n->bound < best_length ) 
	{
		return 1;
	}
	else
	return 0;
}
void get_paths(t_node node)
{
	int i,j; 
	//printf ("*"); 
	if (is_promising(node)) 
	{
		//printf ("<is promising> " );
		if (is_tour(node)) 
		{
			count_tours++; //printf ("<is a tour> " );
			node->level = node->level+1;				// dr. delcher, i completed the path.
			node->path[node->level] = node->path[1];  		

			get_best_path(node);						// keep track of the best path

//			for (i = 1 ; i <= node->level; i++) { printf ("%d ",node->path[i]); } printf (" \n");
		}
		else // for each child of n 
		{
			for (i = 2; i <= d ; i ++ ) 
			{
				if (!in_path(i,node))
				{
					t_node child;
					child=give_birth(node);
					child->bound = get_bound(node) ;
				//	child->level = node->level+1 ;
					child=give_path(node,child);
					child->path[child->level] = i;  // add this node to the path

					for (j=1;j<=( child->level );j++) 
					{ 
						//printf ("%d ",child->path[j]); 
					}

//					//printf ("\n");
					//printf ("\n");

					//printf ("**");
					if (is_promising(child)) 
					{ 	
//						printf ("IN ");
						get_paths(child); 
//						printf ("OUT ");
					}
				}
			}
		}
	}
}
float get_bound(t_node n)
{
//	printf ("\n<") ;
//	printf ("level %d>\n",n->level);

//	if (n->level > 2) 
//	{
//		return(get_length(n));
//	}


	return 0;
}
void main(int argc, char *argv[])
{
	int i;
	if (argc != 1) 
	{
		printf ("Sorry, i don't take command line arguments.\n");
		exit(-1);
	}
	else
	{
		t_node n;					// well heluuu there :)
		init();		
		get_distances();

		n=(t_node)malloc(sizeof(struct s_node));
		n->path =(int *)malloc (d * sizeof (int));
		n->path[1] = 1;
		n->level = 1 ;
		n->bound = get_bound(n); 
		get_paths(n);
	} 
	//printf ( "\n");
//	printf ("\n");
//	printf ("# of tours %d\n",count_tours);
//	printf ("* represents a non-recursive call.\n");
//	printf ("** represents a recursive call.\n");
	printf ( "%f\n",best_length);
	for (i=1;i<=d;i++) { printf("%f %f\n",f1[best_path[i]],f2[best_path[i]]) ; }	//echo best path
}
