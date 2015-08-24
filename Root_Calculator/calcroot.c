#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gmp.h"

void print_root(unsigned int start, unsigned int n, unsigned int precision)
{
	unsigned int xx,step,point,printed;

  printed=0;

	/* Initialize holder to 1 followed by n digits */
	mpz_t holder;
	mpz_init(holder);
	mpz_set_ui(holder,10);
	mpz_pow_ui(holder,holder,n);

  /* Initialize x to the number to take the root of */
	mpz_t x;
	mpz_init(x);
	mpz_set_ui(x,start);

  /* Initialize other variables to use */
  mpz_t delta;
  mpz_init(delta);
	mpz_t subject;
	mpz_init(subject);
	mpz_t hold;
	mpz_init(hold);
	mpz_t hold2;
	mpz_init(hold2);

  mpz_set_ui(delta,0);
  mpz_set_ui(subject,0);

  /* Find how many times x needs to be divided into smaller 
	   portions before we can default to trailing zeroes */
  step=0;
  while(mpz_cmp_ui(x,0)>0)
	{
	  mpz_fdiv_q(x,x,holder);
		step++;
  }

  while(precision>0)
	{
	  precision--;

		/* Bring down the next digits if it can */
		if(step>0)
		{
		  mpz_pow_ui(x,holder,--step);
			mpz_set_ui(hold,start);
			mpz_fdiv_q(x,hold,x);
			mpz_fdiv_r(x,x,holder);	
			mpz_add(subject,subject,x);
	  }

    xx=10;
    mpz_mul_ui(delta,delta,10);

    /* Find the largest value xx such that (delta + xx)^n - delta^n <= subject */
		do
  	{
		  xx--;
			mpz_set(hold,delta);
			mpz_add_ui(hold,hold,xx);
			mpz_pow_ui(hold,hold,n);
			mpz_set(hold2,delta);
			mpz_pow_ui(hold2,hold2,n);
			mpz_sub(hold,hold,hold2);
		}
		while(mpz_cmp(hold,subject)>0);

		printf("%i",xx);
		if(printed==0 && step==0)
		{
		  printf(".");
			printed=1;
		}

    mpz_add_ui(delta,delta,xx);
		mpz_sub(subject,subject,hold);
		mpz_mul(subject,subject,holder);

  }
	
  printf("\n");
}

void main(int argc, char **argv)
{
  print_root(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
}
