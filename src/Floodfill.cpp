// #include "Floodfill.h"
// // nếu ô liền kề có tường bên nào, ta sẽ không điền số bước của xe vào ô bên đó, ngược lại ô đó = ô hiện tại + 1
// int width = 6, height = 6; 

// queue<pair<int, int>> Way; 

// uint8_t maze[6][6] = {                        // tÆ°á»Ÿng á»Ÿ cÃ¡c hÆ°á»›ng trÃªn, dÆ°á»›i, trÃ¡i, pháº£i: XXXX
//     {0b1010, 0b1001, 0b1110, 0b1000, 0b1100, 0b1001},
//     {0b0111, 0b0010, 0b1000, 0b0101, 0b1011, 0b0011},
//     {0b1010, 0b0101, 0b0011, 0b1011, 0b0110, 0b0001},
//     {0b0010, 0b1000, 0b0101, 0b0010, 0b1100, 0b0001},
//     {0b0011, 0b0011, 0b1011, 0b0010, 0b1000, 0b0101},
//     {0b0111, 0b0110, 0b0100, 0b0101, 0b0110, 0b1101},
// };
// int currentDirection = 0;            // 0 Báº¯c 1 ÄÃ´ng 2 Nam 3 TÃ¢y
// int dx[] = {0, 0, -1, 1};            // Di chuyá»ƒn: trÃªn, dÆ°á»›i, trÃ¡i, pháº£i
// int dy[] = {-1, 1, 0, 0};
// int distanceToEnd[6][6];             // Máº£ng khoáº£ng cÃ¡ch

// bool isValid(int y, int x, int dist, int width, int height, uint8_t mazeVal, int direction) {
//     if (y >= 0 && y < height && x >= 0 && x < width && dist == -1) {
//         switch (direction) {
//             case 0: 
//                 if ((mazeVal & 0b1000) != 0 ) return false;   
//                 break;
//             case 1:
//                 if ((mazeVal & 0b0100) != 0) return false;
//                 break;
//             case 2: 
//                 if ((mazeVal & 0b0010) != 0) return false;
//                 break;
//             case 3:
//                 if ((mazeVal & 0b0001) != 0) return false;
//                 break;
//         }
//         return true;
//     }
//     return false;
// }

// void moveForward(){
//    goStraight(oneCell);
// }

// void turnLeft(){
//     turnLeft(90);
//     currentDirection = (currentDirection +3) % 4; 
// }

// void turnRight(){
//     turnRight(90);
//     currentDirection = (currentDirection + 1) % 4;
// }

// // Hàm kiểm tra xem có tường chắn giữa hai ô không
// bool wallBetween(int currentY, int currentX, int nextY, int nextX) {
//     // Kiểm tra tường phía trên (giữa ô hiện tại và ô trên nó)
//     if (nextX == currentX && nextY == currentY - 1) {
//         if ((maze[currentY][currentX] & 0b1000) || (maze[nextY][nextX] & 0b0100)) {
//             return 0; // Có tường chắn ở phía trên
//         }
//     } 
//     // Kiểm tra tường phía dưới
//     else if (nextX == currentX && nextY == currentY + 1) {
//         if ((maze[currentY][currentX] & 0b0100) || (maze[nextY][nextX] & 0b1000)) {
//             return 0; // Có tường chắn ở phía dưới
//         }
//     } 
//     // Kiểm tra tường phía phải
//     else if (nextX == currentX + 1 && nextY == currentY) {
//         if ((maze[currentY][currentX] & 0b0001) || (maze[nextY][nextX] & 0b0010)) {
//             return 0; // Có tường chắn ở phía phải
//         }
//     } 
//     // Kiểm tra tường phía trái
//     else if (nextX == currentX - 1 && nextY == currentY) {
//         if ((maze[currentY][currentX] & 0b0010) || (maze[nextY][nextX] & 0b0001)) {
//             return 0; // Có tường chắn ở phía trái
//         }
//     }
//     return 1; // Không có tường chắn
// }

// // hàm kiểm tra có thể đi đến ô tiếp không
// bool CheckWay(int currentY, int currentX, int nextY, int nextX) {
//     if(distanceToEnd[currentY][currentX] - distanceToEnd[nextY][nextX] == 1  && wallBetween(currentY, currentX, nextY, nextX)){
//         return true;
//     }
//     return false;
// }    

// // hàm quay về hướng cần di chuyển
// void turnToDirection(int currentDirection, int targetDirection){
//     int turnSteps = (targetDirection - currentDirection + 4) % 4; // Đảm bảo kết quả là số dương
//     if (turnSteps == 1) {
//         // Quay phải
//         turnRight(90);
//     } else if (turnSteps == 3) {
//         // Quay trái
//         turnLeft(90);
//     } else if (turnSteps == 2) {
//         turnLeft(180);
//     }
//     else if (turnSteps == 0){
//     }
// }

// // tính hướng di chuyển
// int calculateTargetDirection(int currentX, int currentY, int nextX, int nextY) {
//     if (nextX == currentX && nextY == currentY - 1) {
//         return 0; // Đi lên (Bắc)
//     } else if (nextX == currentX && nextY == currentY + 1) {
//         return 2; // Đi xuống (Nam)
//     } else if (nextX == currentX + 1 && nextY == currentY) {
//         return 1; // Đi phải (Đông)
//     } else if (nextX == currentX - 1 && nextY == currentY) {
//         return 3; // Đi trái (Tây)
//     }
//     return -1; 
// }


// // Hàm để xe có thể quyết định đi sang ô tiếp theo cần rẽ trái hay phải hay đi thẳng (0-Bắc, 1-Đông, 2-Nam, 3-Tây)
// void GoToNextCell(int currentY, int currentX, int nextY, int nextX, int currentDirection) {
//     int targetDirection = calculateTargetDirection(currentX, currentY, nextX, nextY);
//     if (targetDirection != -1) { 
//         turnToDirection(currentDirection, targetDirection);
//         moveForward();
//     } 
// }

// void floodFill(int endY, int endX) {
//     for (int i = 0; i < width; i++) {
//         for (int j = 0; j < height; j++) {
//             distanceToEnd[i][j] = -1; 
//         }
//     }

//     queue<pair<int, int>> Q;   
//     distanceToEnd[endY][endX] = 0;   
//     Q.push({endY, endX});
    
//     while (!Q.empty()) {
//         int a = Q.front().first;
//         int b = Q.front().second;
//         Q.pop();

//         for (int i = 0; i < 4; i++) {
//             int na = a + dy[i];
//             int nb = b + dx[i];

//             if (isValid(na, nb, distanceToEnd[na][nb], width, height, maze[a][b], i)) {
//                 distanceToEnd[na][nb] = distanceToEnd[a][b] + 1;
//                 Q.push({na, nb});
//             }
//         }
//     }
// }

// void findPath(int startY, int startX, int endY,  int endX){
    
//     floodFill(endY, endX);
//     queue<pair<int, int>> Path;
//     Path.push({startY, startX});
//     int distance = distanceToEnd[startY][startX];

//     while(distance >=-1 && !Path.empty()){
//         int a = Path.front().first;
//         int b = .front().second;
//         Way.push({a,b});
//         Path.pop();

//         for (int i = 0; i < 4; i++) {
//             int na = a + dy[i];
//             int nb = b + dx[i];
//         if(CheckWay(a, b, na, nb)){
//             Path.push({na, nb});
//             distance = distanceToEnd[na][nb];
//             break;
//             }
//         }

//     }
// }

// //cho xe chạy
// void SolveMaze(queue<pair<int, int>> &Way) {
//     // Duyệt qua hàng đợi
//     while (Way.size() > 1) { 
//         int Y = Way.front().first;
//         int X = Way.front().second;
//         Way.pop(); 
//         int Y1 = Way.front().first;
//         int X1 = Way.front().second;
//         GoToNextCell(Y, X, Y1, X1, currentDirection);
//     }
// }





