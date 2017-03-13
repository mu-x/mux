#include <string>

class StringTable
{
public:
    typedef std::unordered_map<std::string, size_t> Container;
    typedef Container::iterator Iterator;

    std::shared_ptr<StringTable> instance()
    {
        static const auto inst = std::make_shared<StringTable>();
        return inst;
    }

    Iterator add(std::string string)
    {
        std::lock_guard<std::mutex> g(_mutex);
        const auto itBool = _container.emplace(std::move(string), 1);
        if (!itBool.second)
            // if record exists just increase counter
            ++itBool.first.second;

        return itBool.first;
    }

    void more(Iterator iterator)
    {
        std::lock_guard<std::mutex> g(_mutex);
        ++iterator.second;
    }

    void remove(Iterator iterator)
    {
        std::lock_guard<std::mutex> g(_mutex);
        if (--iter.second == 0)
            // remove if counter reaches zero
            _container.erase(iterator);
    }

private:
    StringTable() = default;
    StringTable(const StringTable&) = delete;

    std::mutex _mutex;
    Container _container;
};

class String
{
public:
    String(std::string string)
        : _table(StringTable::instance())
        , _itrator(_table.add(std::move(string)))
    {
    }

    String(const String& rhs)
        : _table(rhs._table)
        , _iterator(rhs._iterator)
    {
        _table.more(_iterator);
    }

    String(String&& rhs)
        : _table(std::move(rhs._table))
        , _iterator(std::move(rhs._iterator))
    {
        rhs._table = nullptr;
    }

    ~String()
    {
        if (_table)
            _table.remove(_iterator);
    }

    const std::string& string() const { return _iterator->first; }
    operator const std::string&() const { return string(); }

    // TODO: other usefull conversions

private:
    const std::shared_ptr<StringTable> _table;
    const StringTable::Iterator _iterator;
};

int main()
{
    String string1("hello");
    String string2("hello");
}
