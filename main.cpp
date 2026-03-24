#define BOOST_ASIO_HAS_IO_URING 1
#define BUFFER_SIZE 1024

#include <boost/asio.hpp>
#include <iostream>
#include <vector>

std::vector<char> results;

void read_file(boost::asio::io_context& io_context, const std::string& filename) {
    boost::asio::stream_file stream(io_context, filename, boost::asio::stream_file::read_only);

    auto arr = std::make_shared<std::vector<char>>(BUFFER_SIZE);

    stream.async_read_some(
        boost::asio::buffer(*arr),
        [arr](const boost::system::error_code& ec, std::size_t n) {
            if (!ec) {
                std::cout << "Read " << n << " bytes from stream" << std::endl;
                results.insert(results.end(), arr->begin(), arr->begin() + n);
            }
        });
}

int main() {
    boost::asio::io_context io_context;

    read_file(io_context, "file1.txt");
    read_file(io_context, "file2.txt");

    io_context.run();

    for (auto c : results) {
        std::cout << c;
    }

    return 0;
}
