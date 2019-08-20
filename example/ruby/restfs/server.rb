#!/usr/bin/env ruby

require 'sinatra'
require 'sinatra/namespace'
require 'fileutils'

API_SUFFIX=''
ROOT_DIR = ARGV[0] || '/tmp'

if ARGV.size > 1 then
    print "Usage: <this> [directory_path]\n"
    exit 1
end

print "Selected directory: #{ROOT_DIR}\n"
namespace API_SUFFIX do
    get '/*' do |path|
        path = path ? File.join(ROOT_DIR, path) : ROOT_DIR
        return File.read(path) if File.file? path

        def type p
            return 'file' if File.file? p
            return 'directory' if File.directory? p
            return 'unknown'
        end

        begin
            content = Dir.entries(path)
                .select { |i| i != '.' && i != '..' }
                .map { |i| { "name" => i, "type" => type(File.join(path, i)) } }
                .select { |i| i['type'] != 'unknown' }
        rescue Errno::ENOENT => error
            status 404
            return "#{error}"
        end

        content_type 'application/json'
        content.to_json
    end

    put '/*' do |path|
        path = path ? File.join(ROOT_DIR, path) : ROOT_DIR
        print "----- #{params}\n"

        begin
            if params.key?('directory') || params.key?('d') then
                Dir.mkdir(path)
            else
                File.open(path, "w") { |file| file.puts request.body.read }
            end
        rescue Errno::ENOENT => error
            status 404
            return "#{error}"
        rescue Errno::EEXIST => error
            status 406
            return "#{error}"
        end

        status 201
    end

    delete '/*' do |path|
        path = path ? File.join(ROOT_DIR, path) : ROOT_DIR
        FileUtils.rm_rf(path)
        status 204
    end
end

