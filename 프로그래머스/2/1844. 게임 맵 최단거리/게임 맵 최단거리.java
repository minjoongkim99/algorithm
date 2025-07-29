import java.util.*;

class Solution {
    
    private static int N;
    private static int M;
    
    private static int[] dy = {-1, 0, 1, 0};
    private static int[] dx = {0, 1, 0, -1};
    
    
    public int solution(int[][] maps) {
        int answer = 0;
        
        N = maps.length;
        M = maps[0].length;
        
        int [][] visited = new int [N][M];
        
        
        Queue<int[]> q = new LinkedList<>();
        q.add(new int[]{0, 0});
        visited[0][0] = 1;
        
        while(!q.isEmpty()){
            
            int []cur = q.poll();
            int y = cur[0];
            int x = cur[1];
            
            for(int dir = 0; dir < 4; ++dir){
                int yy = y + dy[dir];
                int xx = x + dx[dir];
                
                if(yy < 0 || yy >= N || xx < 0 || xx >= M) continue;
                if(maps[yy][xx] == 0) continue;
                if(visited[yy][xx] > 0) continue;
                
                q.offer(new int[] {yy, xx});
                visited[yy][xx] = visited[y][x] + 1;
            }
        }
        
        
        if(visited[N - 1][M - 1] == 0)
            answer = -1;
        else answer = visited[N - 1][M - 1];
        
        return answer;
    }
}