start = ARGV[0].to_i
n = ARGV[1].to_i
precision = ARGV[2].to_i

printed = 0

# Initialize holder to 1 followed by n digits
holder = 10 ** n

# Initialize x to the number to take the root of
x = ARGV[0].to_i

# Initialize other variables to use
delta = 0
subject = 0

# Find how many times x needs to be divided into smaller
# portions before we can default to trailing zeroes

step = 0

while x > 0
  x = x/holder
  step = step+1
end

while precision > 0
  precision = precision-1

  # Bring down the next digits if it can
  if step > 0
    step = step-1
    subject = (start/(holder ** step))%holder + subject
  end

  xx = 10
  delta = delta*10

  # Find the largest value xx such that (delta + xx)^n - delta^n <= subject
  begin
    xx = xx-1
    hold = (delta + xx)**n - delta**n
  end while hold > subject

  print xx

  if printed==0 && step==0
    print "."
    printed = 1
  end

  delta = delta + xx
  subject = (subject - hold)*holder
end
puts
