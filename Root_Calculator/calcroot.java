import static java.lang.System.out;
import java.math.*;

public class calcroot
{
  public static void main(String []args)
  {
    int xx,step,point,printed,start,n,precision;

    start = Integer.parseInt(args[0]);
    n = Integer.parseInt(args[1]);
    precision = Integer.parseInt(args[2]);

    printed = 0;

    /* Initialize holder to 1 followed by n digits */
    BigInteger holder = BigInteger.TEN.pow(n);

    /* Initialize x to the number to take the root of */
    BigInteger x = BigInteger.valueOf(start);

    /* Initialize other variables to use */
    BigInteger delta = BigInteger.ZERO;
    BigInteger subject = BigInteger.ZERO;
    BigInteger hold;
    BigInteger hold2;

    /* Find how many times x needs to be divided into smaller
       portions before we can default to trailing zeroes */

    step=0;
    while(x.compareTo(BigInteger.ZERO) > 0)
    {
      x = x.divide(holder);
      step++;
    }

    while(precision>0)
    {
      precision--;

      /* Bring down the next digits if it can */
      if(step>0)
      {
        subject = BigInteger.valueOf(start).divide(holder.pow(--step)).remainder(holder).add(subject);
      }

      xx=10;
      delta = delta.multiply(BigInteger.TEN);

      /* Find the largest value xx such that (delta + xx)^n - delta^n <= subject */
      do
      {
        xx--;
        hold = delta.add(BigInteger.valueOf(xx)).pow(n).subtract(delta.pow(n));
      }
      while(hold.compareTo(subject)>0);

      out.format("%d",xx);

      if(printed==0 && step==0)
      {
        out.print(".");
        printed=1;
      }

      delta = delta.add(BigInteger.valueOf(xx));
      subject = subject.subtract(hold).multiply(holder);
    }
    out.println();
  }
}
