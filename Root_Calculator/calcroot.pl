use bignum;

$start = $ARGV[0];
$n = $ARGV[1];
$precision = $ARGV[2];

$printed = 0;

# Initialize holder to 1 followed by n digits
$holder = 10 ** $n;

# Initialize x to the number to take the root of
$x = $ARGV[0];

# Initialize other variables to use
$delta = 0;
$subject = 0;

# Find how many times x needs to be divided into smaller
# portions before we can default to trailing zeroes

$step = 0;

while ($x > 1)
{
   $x = $x/$holder;
   $step = $step + 1;
}

while ($precision > 0)
{
  $precision = $precision - 1;

  # Bring down the next digits if it can
  if ($step > 0)
  {
    $step = $step - 1;
    $subject = ($start/($holder ** $step))%$holder + $subject;
  }

  $xx = 10;
  $delta = $delta * 10;

  # Find the largest value xx such that (delta + xx)^n - delta^n <= subject
  do
  {
    $xx = $xx - 1;
    $hold = ($delta + $xx)**$n - $delta**$n;
  }
  while($hold > $subject);

  print $xx;

  if($printed == 0 && $step == 0)
  {
    print '.';
    $printed = 1;
  }

  $delta = $delta + $xx;
  $subject = ($subject - $hold)*$holder;
}
print "\n";
