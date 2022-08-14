
    echo "TEST b"
    ./s21_cat -b 1.txt >s21_cat_result
    cat -b 1.txt >cat_result
    diff -s s21_cat_result cat_result
    
    echo "TEST e"
    ./s21_cat -e 1.txt >s21_cat_result
    cat -e 1.txt >cat_result
    diff -s s21_cat_result cat_result

    echo "TEST n"
    ./s21_cat -n 1.txt >s21_cat_result
    cat -n 1.txt >cat_result
    diff -s s21_cat_result cat_result

    echo "TEST s"
    ./s21_cat -s 1.txt >s21_cat_result
    cat -s 1.txt >cat_result
    diff -s s21_cat_result cat_result

    echo "TEST t"
    ./s21_cat -t 1.txt >s21_cat_result
    cat -t 1.txt >cat_result
    diff -s s21_cat_result cat_result

    echo "TEST v"
    ./s21_cat -v 1.txt >s21_cat_result
    cat -v 1.txt >cat_result
    diff -s s21_cat_result cat_result

    echo "TEST number"
    ./s21_cat --number 1.txt >s21_cat_result
    cat -n 1.txt >cat_result
    diff -s s21_cat_result cat_result

    echo "TEST number-nonblank"
    ./s21_cat --number-nonblank 1.txt >s21_cat_result
    cat -b 1.txt >cat_result
    diff -s s21_cat_result cat_result    

    echo "TEST squeeze-blank"
    ./s21_cat --squeeze-blank 1.txt >s21_cat_result
    cat -s 1.txt >cat_result
    diff -s s21_cat_result cat_result   


rm -rf s21_cat_result cat_result
