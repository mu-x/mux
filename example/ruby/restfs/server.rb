#!/usr/bin/env ruby

require 'sinatra'
require 'sinatra/namespace'

require './file_system.rb'

API_SUFFIX = ''
ROOT_DIR = ARGV[0] || '/tmp'

if ARGV.size > 1 then
  print "Usage: <this> [directory_path]\n"
  exit 1
end

file_system = FileSystem.new(ROOT_DIR)
namespace API_SUFFIX do
  get '/*' do |path|
    unless (content = file_system.content(path)).nil?
      # TODO: find out and supply content_type.
      return content
    end
    begin
      content = file_system.subitems(path)
    rescue Errno::ENOENT => error
      status 404; "#{error}"
    else
      content_type 'application/json'
      status 200; content.to_json
    end
  end

  put '/*' do |path|
    begin
      if params.key?('directory') || params.key?('d')
        file_system.create_directory(path)
      else
        file_system.save_file(path, request.body.read)
      end
      status 201
    rescue Errno::ENOENT => error
      status 404; "#{error}"
    rescue Errno::EEXIST => error
      status 406; "#{error}"
    end
  end

  delete '/*' do |path|
    begin
      file_system.delete(path, directory?: params.key?('directory') || params.key?('d'))
      status 204
    rescue Errno::EEXIST => error
      status 406; "#{error}"
    end
  end
end
