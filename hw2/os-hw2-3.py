import multiprocessing

def worker_function(result_queue):
    sum = 0
    for i in range(21_000_000_000):
        sum += i
    result_queue.put(sum)

if __name__ == "__main__":
    multiprocessing.freeze_support()  # 이 줄을 추가합니다.

    # 프로세스 생성
    processes = []
    result_queue = multiprocessing.Queue()
    for _ in range(10):
        process = multiprocessing.Process(target=worker_function, args=(result_queue,))
        processes.append(process)
        process.start()

    # 프로세스 종료 대기
    for process in processes:
        process.join()

    # 결과 출력
    while not result_queue.empty():
        print("Worker result:", result_queue.get())
