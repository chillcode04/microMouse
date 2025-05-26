#define MAX_X 15// Giới hạn kích thước ma trận theo chiều ngang
#define MAX_Y 15  // Giới hạn kích thước ma trận theo chiều dọc

int count[MAX_X][MAX_Y] = {0}; 
std::stack<std::pair<u32, u32>> s_final;

void optimizePath(std::stack<std::pair<u32, u32>>& s) {
    auto current = s.top();
    while (count[current.first][current.second] > 1 && !s.empty()) {
        s.pop();
        count[current.first][current.second]--;        
    }
    s_final.push(current);
}