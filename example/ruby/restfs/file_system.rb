require 'fileutils'

class FileSystem
  def initialize root
    @root = root
  end

  def path(path)
    File.join(@root, path)
  end

  def content(path)
    path = self.path(path)
    File.read(path) if File.file?(path)
  end

  def subitems(path)
    path = self.path(path)
    Dir.entries(path)
      .select { |i| i != '.' && i != '..' }
      .map { |i| { "name" => i, "type" => self.class.item_type(path, i) } }
      .select { |i| i['type'] != 'unknown' }
  end

  def save_file(path, content)
    File.open(self.path(path), "w") { |file| file.puts(content) }
  end

  def create_directory(path)
    Dir.mkdir(self.path(path))
  end

  def delete(path, directory: false)
    if directory
      FileUtils.remove_dir(self.path(path))
    else
      File.delete(self.path(path))
    end
  end

  def self.item_type(dir, item)
    path = File.join(dir, item)
    return 'file' if File.file?(path)
    return 'directory' if File.directory?(path)
    'unknown'
  end
end
