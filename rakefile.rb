PROJECT_ROOT  = File.expand_path( File.dirname(__FILE__) )

load '../ceedling/lib/rakefile.rb'

task :default => ['test:all']
