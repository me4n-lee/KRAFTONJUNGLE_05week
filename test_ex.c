RB-INSERT(t, z)

    y = t.nil                   // y를 NIL로 초기화
    x = t.root                  // x를 루트로 설정

    // Case 1: 트리가 비어있는 경우 또는 적절한 위치를 찾을 때까지
    while x != t.nil            // x가 NIL이 아닐 때까지
        y = x                   // y를 x로 업데이트

        if z.key < x.key        // 삽입할 값이 현재 노드의 키보다 작으면
            x = x.left          // 왼쪽으로 이동
        else                    // 삽입할 값이 현재 노드의 키보다 크거나 같으면
            x = x.right         // 오른쪽으로 이동

    z.p = y                     // z의 부모를 y로 설정

    // Case 2: 새 노드가 루트 노드가 될 경우
    if y == t.nil               // 트리가 비어 있으면
        t.root = z              // z를 루트로 설정
    // Case 3: 새 노드가 부모 노드의 왼쪽 자식이 될 경우
    elseif z.key < y.key        // z의 키가 y의 키보다 작으면
        y.left = z              // z를 y의 왼쪽 자식으로 설정
    // Case 4: 새 노드가 부모 노드의 오른쪽 자식이 될 경우
    else                        // z의 키가 y의 키보다 크거나 같으면
        y.right = z             // z를 y의 오른쪽 자식으로 설정

    z.left = t.nil              // z의 왼쪽 자식을 NIL로 설정
    z.right = t.nil             // z의 오른쪽 자식을 NIL로 설정
    z.color = RED               // z의 색을 레드로 설정

    RB-INSERT-FIXUP(t, z)       // 레드-블랙 트리 속성을 유지하도록 수정



RB-INSERT-FIXUP(t, z)

// Case 1: z의 부모 노드가 RED일 때까지 반복
while z.p.color == RED                      // z의 부모의 색이 레드일 때까지
    // Case 2: z의 부모가 z의 할아버지의 왼쪽 자식일 경우
    if z.p == z.p.p.left                    // z의 부모가 왼쪽 자식이면
        y = z.p.p.right                     // y를 z의 삼촌으로 설정
        
        // Case 2.1: z의 삼촌이 RED일 경우
        if y.color == RED                   // y의 색이 레드면
            z.p.color = BLACK               // z의 부모의 색을 블랙으로 변경
            y.color = BLACK                 // y의 색을 블랙으로 변경
            z.p.p.color = RED               // z의 할아버지의 색을 레드로 변경
            z = z.p.p                       // z를 z의 할아버지로 업데이트
        else
            // Case 2.2: z가 부모의 오른쪽 자식이고, 삼촌이 BLACK인 경우
            if z == z.p.right               // z가 부모의 오른쪽 자식이면
                z = z.p                     // z를 z의 부모로 업데이트
                LEFT-ROTATE(t, z)           // z를 중심으로 왼쪽 회전

            z.p.color = BLACK               // z의 부모의 색을 블랙으로 변경
            z.p.p.color = RED               // z의 할아버지의 색을 레드로 변경
            RIGHT-ROTATE(t, z.p.p)          // z의 할아버지를 중심으로 오른쪽 회전

    else // Case 3: z의 부모가 z의 할아버지의 오른쪽 자식일 경우
        y = z.p.p.left                      // y를 z의 삼촌으로 설정

        // Case 3.1: z의 삼촌이 RED인 경우
        if y.color == RED:
            z.p.color = BLACK               // z의 부모의 색을 블랙으로 변경
            y.color = BLACK                 // y의 색을 블랙으로 변경
            z.p.p.color = RED               // z의 할아버지의 색을 레드로 변경
            z = z.p.p                       // z를 z의 할아버지로 업데이트
        else:
            // Case 3.2: z가 부모의 왼쪽 자식이고, 삼촌이 BLACK인 경우
            if z == z.p.left:               // z가 부모의 왼쪽 자식이면
                z = z.p                     // z를 z의 부모로 업데이트
                RIGHT-ROTATE(t, z)          // z를 중심으로 오른쪽 회전

            z.p.color = BLACK               // z의 부모의 색을 블랙으로 변경
            z.p.p.color = RED               // z의 할아버지의 색을 레드로 변경
            LEFT-ROTATE(t, z.p.p)           // z의 할아버지를 중심으로 왼쪽 회전

    t.root.color = BLACK                    // 트리의 루트를 블랙으로 변경


LEFT-ROTATE(t, x)

    y = x.right                 // x의 오른쪽 자식을 y로 설정
    x.right = y.left            // y의 왼쪽 서브트리를 x의 오른쪽 서브트리로 설정

    if y.left != t.nil
        y.left.p = x            // y의 왼쪽 자식의 부모를 x로 설정
    
    y.p = x.p                   // y의 부모를 x의 부모로 설정

    if x.p == t.nil
        t.root = y              // x의 부모가 없는 경우 (즉, x가 root인 경우), y를 새로운 root로 설정
    elseif x == x.p.left
        x.p.left = y            // x가 왼쪽 자식인 경우, x의 부모의 왼쪽 자식을 y로 설정
    else
        x.p.right = y           // x가 오른쪽 자식인 경우, x의 부모의 오른쪽 자식을 y로 설정
    
    y.left = x                  // y의 왼쪽 자식을 x로 설정
    x.p = y                     // x의 부모를 y로 설정

RB-TRANSPLANT(t, u, v)

    if u.p == t.nil           // u가 root 노드인 경우
        t.root = v            // v를 새로운 root로 설정
    else if u == u.p.left     // u가 부모의 왼쪽 자식인 경우
        u.p.left = v          // u의 부모의 왼쪽 자식을 v로 설정
    else                      // u가 부모의 오른쪽 자식인 경우
        u.p.right = v         // u의 부모의 오른쪽 자식을 v로 설정
    
    v.p = u.p                 // v의 부모를 u의 부모로 설정

RB-DELETE-FIXUP(t, x)

    while x != t.root and x.color == BLACK                          // x가 루트가 아니고, 색이 블랙인 동안 반복
        if x == x.p.left                                            // x가 부모의 왼쪽 자식인 경우
            w = x.p.right                                           // w를 x의 형제 노드로 설정
            
            if w.color == RED                                       // w의 색이 레드인 경우 (Case 1)
                w.color = BLACK                                     // w를 블랙으로 바꿈
                x.p.color = RED                                     // x의 부모를 레드로 바꿈
                LEFT-ROTATE(t, x.p)                                 // x의 부모를 기준으로 왼쪽 회전
                w = x.p.right                                       // w를 x의 형제 노드로 다시 설정 (w의 색은 블랙)

            if w.left.color == BLACK and w.right.color == BLACK     // w의 두 자식이 모두 블랙인 경우 (Case 2)
                w.color = RED                                       // w를 레드로 바꿈
                x = x.p                                             // x를 부모로 업데이트
            else 
                if w.right.color == BLACK                           // w의 오른쪽 자식이 블랙인 경우 (Case 3)
                    w.left.color = BLACK                            // w의 왼쪽 자식을 블랙으로 바꿈
                    w.color = RED                                   // w를 레드로 바꿈
                    RIGHT-ROTATE(t, w)                              // w를 기준으로 오른쪽 회전
                    w = x.p.right                                   // w를 x의 형제 노드로 다시 설정 (w의 색은 블랙)
                
                w.color = x.p.color                                 // w의 색을 x의 부모의 색으로 바꿈
                x.p.color = BLACK                                   // x의 부모의 색을 블랙으로 바꿈
                w.right.color = BLACK                               // w의 오른쪽 자식의 색을 블랙으로 바꿈
                LEFT-ROTATE(t, x.p)                                 // x의 부모를 기준으로 왼쪽 회전
                x = t.root                                          // x를 루트로 업데이트

        else                                                        // x가 부모의 오른쪽 자식인 경우. 위의 조건과 대칭적임.
            w = x.p.left                                            // w를 x의 형제 노드로 설정

            if w.color == RED                                       // w의 색이 레드인 경우
                w.color = BLACK                                     // w를 블랙으로 바꿈
                x.p.color = RED                                     // x의 부모를 레드로 바꿈
                RIGHT-ROTATE(t, x.p)                                // x의 부모를 기준으로 오른쪽 회전
                w = x.p.left                                        // w를 x의 형제
            
            if w.right.color == BLACK and w.left.color == BLACK     // w의 두 자식이 모두 블랙인 경우 (Case 2)
                w.color = RED                                       // w를 레드로 바꿈
                x = x.p                                             // x를 부모로 업데이트
            else 
                if w.left.color == BLACK                            // w의 왼쪽 자식이 블랙인 경우 (Case 3)
                    w.right.color = BLACK                           // w의 오른쪽 자식을 블랙으로 바꿈
                    w.color = RED                                   // w를 레드로 바꿈
                    LEFT-ROTATE(t, w)                               // w를 기준으로 왼쪽 회전
                    w = x.p.left                                    // w를 x의 형제 노드로 다시 설정 (w의 색은 블랙)

                w.color = x.p.color                                 // w의 색을 x의 부모의 색으로 바꿈
                x.p.color = BLACK                                   // x의 부모의 색을 블랙으로 바꿈
                w.left.color = BLACK                                // w의 왼쪽 자식의 색을 블랙으로 바꿈
                RIGHT-ROTATE(t, x.p)                                // x의 부모를 기준으로 오른쪽 회전
                x = t.root                                          // x를 루트로 업데이트

    x.color = BLACK                                                 // x의 색을 블랙으로 바꿈 (루트 노드는 항상 블랙)


RB-ERASE(t, z)

    y = z                                   // y를 삭제할 노드 z로 설정
    y-original-color = y.color              // y의 원래 색을 저장

    // z의 왼쪽 자식이 없는 경우
    if z.left = t.nil
        x = z.right                         // x를 z의 오른쪽 자식으로 설정
        RB-TRANSPLANT(t, z, z.right)        // z를 z의 오른쪽 자식으로 대체

    // z의 오른쪽 자식이 없는 경우
    elseif z.right == t.nil
        x = z.left // x를 z의 왼쪽 자식으로 설정
        RB-TRANSPLANT(t, z, z.left)         // z를 z의 왼쪽 자식으로 대체

    // z의 양쪽 자식이 모두 있는 경우
    else
        y= TREE-MIN(z.right)                // y를 z의 오른쪽 서브트리에서 가장 작은 노드로 설정
        y-original-color = y.color          // y의 원래 색을 저장
        x = y.right // x를 y의 오른쪽 자식으로 설정

        // y가 z의 직접적인 오른쪽 자식인 경우
        if y.p == z
            x.p = y                         // x의 부모를 y로 설정

        // y가 z의 오른쪽 서브트리에서 더 아래에 있는 경우
        else
            RB-TRANSPLANT(t, y, y.right)    // y를 y의 오른쪽 자식으로 대체
            y.right = z.right               // y의 오른쪽 자식을 z의 오른쪽 자식으로 설정
            y.right.p = y                   // y의 오른쪽 자식의 부모를 y로 설정
        
        // z를 y로 대체
        RB-TRANSPLANT(t, z, y)
        y.left = z.left                     // y의 왼쪽 자식을 z의 왼쪽 자식으로 설정
        y.left.p = y                        // y의 왼쪽 자식의 부모를 y로 설정
        y.color = z.color                   // y의 색을 z의 색으로 설정

    // y의 원래 색이 BLACK인 경우, 레드-블랙 트리의 속성을 복구
    if y-original-color == BLACK
        RB-DELETE-FIXUP(t, x)