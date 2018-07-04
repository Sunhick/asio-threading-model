## ASIO sample code
```
asio::io_service io_service;
asio::io_service::work work(io_service);

std::this_thread::set_name("ui::main");

std::vector<std::thread> threadPool;

for (size_t t = 0; t < std::thread::hardware_concurrency(); t++) {
// threadPool.push_back(thread(std::bind(&asio::io_service::run,
// &io_service)));
// std::cout << "::" << t << std::endl;
std::size_t (asio::io_service::*run)() = &asio::io_service::run;
threadPool.push_back(std::thread([&, t] {
std::this_thread::set_name("worker:" + std::to_string(t));
std::bind(run, &io_service);
}));
}

// name of the current thread
std::cout << "Main thread: " << std::this_thread::get_name() <<
std::endl;

io_service.post([]() {
std::cout << "hello" << std::endl;
});
//    io_service.post(std::bind(task2, 123, "Sunil"));

io_service.run();
std::cout << "done" << std::endl;
// io_service.stop();
for (std::thread& t : threadPool) {
t.join();
}
```
