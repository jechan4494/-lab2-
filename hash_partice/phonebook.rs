use std::collections::HashMap;
use std::io::{self, Write};

fn main() {
    let mut phonebook: HashMap<String, String> = HashMap::new();

    println!("=== 전화번호부 프로그램 ===");

    loop {
        print!("\n1) 추가  2) 검색  3) 전체 보기  4) 종료\n선택: ");
        io::stdout().flush().unwrap();

        let mut input = String::new();
        if io::stdin().read_line(&mut input).is_err() {
            println!("입력을 읽는 데 실패했습니다.");
            continue;
        }

        match input.trim() {
            "1" => {
                // 전화번호 추가
                print!("이름: ");
                io::stdout().flush().unwrap();
                let mut name = String::new();
                io::stdin().read_line(&mut name).unwrap();

                print!("전화번호: ");
                io::stdout().flush().unwrap();
                let mut phone = String::new();
                io::stdin().read_line(&mut phone).unwrap();

                let name = name.trim().to_string();
                let phone = phone.trim().to_string();
                phonebook.insert(name.clone(), phone);

                println!("'{}'님의 번호가 저장되었습니다.", name);
            }
            "2" => {
                // 검색
                print!("검색할 이름: ");
                io::stdout().flush().unwrap();
                let mut name = String::new();
                io::stdin().read_line(&mut name).unwrap();
                let name = name.trim();

                if let Some(phone) = phonebook.get(name) {
                    println!("{}님의 전화번호: {}", name, phone);
                } else {
                    println!("'{}' 님을 찾을 수 없습니다.", name);
                }
            }
            "3" => {
                // 전체 보기
                if phonebook.is_empty() {
                    println!("전화번호부가 비어 있습니다.");
                } else {
                    println!("--- 전체 목록 ---");
                    for (name, phone) in &phonebook {
                        println!("- {}: {}", name, phone);
                    }
                }
            }
            "4" => {
                println!("프로그램을 종료합니다.");
                break;
            }
            _ => {
                println!("잘못된 선택입니다. 1, 2, 3, 4 중 하나를 입력하세요.");
            }
        }
    }  }
