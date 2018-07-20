#!ruby

puts "["
prefix = ""
40000.times {
    puts "#{prefix}{ \"kind\":0, \"category\":1003, \"account\":1007, \"date\":\"2013.4.25\", \"value\":105000.00 }"
    prefix = ","
}
puts "]"
