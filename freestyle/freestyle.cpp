#include <SFML/Graphics.hpp>
#include <iostream>
#include<random>
//class TileMap : public sf::Drawable, public sf::Transformable
//{
//public:
//    bool load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
//    {
//        // load the tileset texture
//        if (!m_tileset.loadFromFile(tileset))
//            return false;
//
//        // resize the vertex array to fit the level size
//        m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
//        m_vertices.resize(width * height * 6);
//
//        // populate the vertex array, with two triangles per tile
//        for (unsigned int i = 0; i < width; ++i)
//        {
//            for (unsigned int j = 0; j < height; ++j)
//            {
//                // get the current tile number
//                const int tileNumber = tiles[i + j * width];
//
//                // find its position in the tileset texture
//                const int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
//                const int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
//
//                // get a pointer to the triangles' vertices of the current tile
//                sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];
//
//                // define the 6 corners of the two triangles
//                triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
//                triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
//                triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
//                triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
//                triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
//                triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
//
//                // define the 6 matching texture coordinates
//                triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
//                triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
//                triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
//                triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
//                triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
//                triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
//            }
//        }
//
//        return true;
//    }
//
//private:
//    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
//    {
//        // apply the transform
//        states.transform *= getTransform();
//
//        // apply the tileset texture
//        states.texture = &m_tileset;
//
//        // draw the vertex array
//        target.draw(m_vertices, states);
//    }
//
//    sf::VertexArray m_vertices;
//    sf::Texture     m_tileset;
//};
//int main()
//{
//    // create the window
//    sf::RenderWindow window(sf::VideoMode({ 1024, 512 }), "Tilemap");
//
//    // define the level with an array of tile indices
//    constexpr std::array level = {
//        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
//        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
//        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
//        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
//        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
//        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
//        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
//        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
//        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
//        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
//        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
//        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//
//    };
//
//    // create the tilemap from the level definition
//    TileMap map;
//    if (!map.load("tileset.png", { 32, 32 }, level.data(), 16, 16))
//        return -1;
//
//    // run the main loop
//    while (window.isOpen())
//    {
//        // handle events
//        while (const std::optional event = window.pollEvent())
//        {
//            if (event->is<sf::Event::Closed>())
//                window.close();
//        }
//
//        // draw the map
//        window.clear();
//        window.draw(map);
//        window.display();
//    }
//}
//
////int main() {
////    sf::RenderWindow window(sf::VideoMode({ 600, 900 }), "Font Test");
////
////    while (window.isOpen()) {
////        while (const std::optional event = window.pollEvent()) 
////            { 
////                if (event->is<sf::Event::Closed>()) window.close(); 
////            } 
////        window.clear(); 
////
////
////        window.display(); 
////    }
////
////    return 0;
////}
///*
// văn bản cũng có thể được chuyển đổi: chugns có bị trí, hướng và tỷ lệ, các chức năng liên quan 
// giống sf::Sprite  và các thực thể sfml khác
//
// làm thế nào để tránh vấn đề liên quan đến các ký tự không phải ascii
// xử lý đúng các ký tự như kiểu ký tự châu âu có dấu, tiếng ả rập, trung quốc, tiếng việt
// cách tốt nhất là sử dụng chuỗi ký tự rộng, hiểu đơn giản là thêm tiền tố L ở trước xâu đó
//    ví dụ: text.setString(L"chóa");
//    Tiền tố L đơng giản là yêu cầu trình biên dịch tạo ra một cuỗi rộng , chuỗi rộng là 1 con quái vật kỳ lạ trong c++, tiêu chuẩn không nói gì về kích thước của chúng, cũng không nói về mã hóa mà chúng sử dụng 
//tuy nhiên, chúng ta biết rằng hầu hết các nền tảng, nếu không muốn nói là tất cả, chúng sẽ tạo ra các chuỗi Unicode và sfml biết cách xử lý chúng 1 cách chihs xác
//    Lưu ý rằng: chuẩn c++11 hỗ trợ cac kiểu ký tự và tiền tố mới để xây dựng các chuỗi UTF-8 ,UTF-16, UTF-32
//    
//
//    TẠO LỚP VĂN BẢN CỦA RIÊNG BẠN
//
//    Nếu sf::text quá hạn chế, bạn muốn làm gì đó khác với các ký tự tượng hình đc dựng sẵn thì sf::Font nó sẽ cung cấp cho bạn
//bạn có thể lấy lại kết cấu chứa tất cả các ký tự tượng hình đc dựng sẵn có kích thước nhất định
//
//        const sf::Texture& texture = font.getTexture(characterSize);
//
//    Để làm gì đó có ý nghĩa với họa tiết phông chữ, bạn sẽ phải lấy tọa độ họa tiết của các ký tự tượng hình trong phông chữ đó:
//    
//        sf::Glypj glyph = font.getPlyph(character,characterSize,bold);
//
//    character là mã UTF-32 của  ký tự có glyph mà bạn muốn lấy, bạn cũng cần phải chỉ định kích thước và ký tự và bạn muốn glyph dạng in đậm hay thông thường
//    
//    Cấu trúc sf::Glypj chưa 3 thành phần dữ liệu chính: 
//    - advance: độ lẹch ngang đc áp dụng để có đc vị trí bắt đầu của ký tựu tượng hình tiếp theo trong văn bản
//    - bounds: chứa hình chữ nhật giới hạn của ký tự tượng hình, giúp định vị so với đường cơ sở của văn bản
//    - textureRect: chứa tọa độ kết cấu của ký tự tượng hình trong kết cấu
//
//    bạn cũng có thể lấy 1 số liệu khác của phông chữ, chẳng hạn như khoảng cách giữa 2 ký tự hoặc cách dòng( luôn dòng cho 1 kích thước ký tự nhất định:
//    float lineSpacing = font.getLinesSpacing(CharacterSize);
//    float kerning = font.getKerning(character1,character2,character3);
//
//
//
//    HÌNH ẢNH
//
//    MÀU SẮC
//    một trong những đặc tính cơ bản của hình danh là màu sắc của nó. bạn có thể thay đổi bằng setFillColor 
//    sf::CircleShape shape(50.f);
//    //set the shape color to green
//    shape.setFillColor(sf::Color(100,250,50));
//
//    hình dạng có thể có đường viền. bạn có thể thiết lập độ dày và màu sắc của đường viện bằng các hàm setOutlineThickness và setOutlineColor
//
//    sf::CircleShape shape(50.f);
//    shape.setFillColor(sf::Color(100,250,50));
//
//    //set a 10-pixel wide orange outline
//    shape.setOutlineThickness(10.f)
//    shape.setOutlineColor(sf::Color(250,150,100));
//
//    nếu ta fill trực tiếp như vậy thì hình tròn sẽ bị đẩy lùi ra ngoài, để vô hiệu hóa đường viền, hãy đặt độ dày của đường viền thành 0,nếu bạn có thể đặt màu tô thành sf::Color::Transparent
//
//    A.CÁC LOẠI HÌNH DẠNG TÍCH HỢP
//    
//        - HÌNH CHỮ NHẬT
//            để vẽ hình chữ nhật, bạn có thể sử dụng sf::RectangleShape, lớp này có 1 thuộc tính duy nhất: kích thước của hình chữ nhật
//                
//                // define a 120x50 rectangle
//                sf::RectangleShape rectangle({120.f,50.f})
//
//                // change the size to 100x100
//                rectagle.setSize({100.f,100.f})
//
//        - HÌNH TRÒN
//            các vòng tròn đc biểu diễn bởi sf::CircleShape, nó có 2 thuộc tính, bán kính và số cạnh.Số cạnh là 1 thuộc tính tùy chọn, nó cho phép điều chỉnh chất lượng của vòng tròn
//        các vòng tròn phải được xấp xỉ bằng các đa giác có nhiều cạnh( card đồ họa không thể vẽ trực tiếp 1 vòng tròn hoàn hảo) và thuộc tính này xác định số cạnh mà phép xấp xỉ vòng tròn của bạn sẽ có
//        nếu bạn vẽ vòng tròn nhỏ, có lẽ chỉ cần vài cạnh, còn vẽ vòn tròn lớn hơn thì cần nhiều hơn
//
//                //define a circle with radius = 200
//                sf::CircleShape circle(200.f);
//
//                // change the radius to 40
//                circle.setRadius(40.f);
//
//                // change the number of sides(points) to 100
//                circle.setPointCount(100);
//
//        - ĐA GIÁC ĐỀU
//            không có class chuyên dụng nào dành cho đa giác đều, trên thực tế, bạn có thể biểu diễn 1 đa giác đều với bất kì số cạnh nào bằng cách sử dụng CircleShape, vì hình tròn đc xấp xỉ bằng đa giác nhiều cạnh
//        bạn chỉ cần bắt đầu với số cạnh để có đc đa giác mong muốn. một mình sf::CircleShape có 3 điểm là hình tam giác, với 4 điểm sẽ là hình vuông,...
//                
//                #define a triangle
//                sf::CircleShape triangle(80f,3);
//
//                //define a square
//                sf::CircleShape square(80.f,4);
//
//                #define a octagon
//                sf::CircleShape octagon(80.f ,5);
//
//        - ĐA GIÁC LỒI
//            lớp này sf::ConvexShape là hình dạng cuối cùng: nó cho phép bạn xác định bất kì hình dạng lồi nào.sfml không thể vẽ các hình dạng lõm. nếu bạn cần vẽ 1 hình dạng lõm bạn sẽ phải chia nó thành nhiều đa giác lỗi.
//        để tạo 1 hình lồi, trước tiên phải thiết lập 1 số điểm cần có và sau đó xác định các điểm đó
//
//                //create an empty shape
//                sf::ConvexShape convex;
//
//                //resize it to 5 points
//                convex.setPointCount(5);
//
//                // define the points
//                convex.setPoint(0,{0.f,0.f});
//                convex.setPoint(1,{150.f,10.f});
//                convex.setPoint(2,{120.f,90.f});
//                convex.setPoint(3,{30.f,100.f});
//                convex.setPoint(4,{0.f,50.f});
//
//        - ĐƯỜNG THẲNG
//            không có hình dạng nào cho các đường thẳng, lý do đơn giản, nếu đường thẳng của bạn có độ dày thì nó sẽ là hình chữ nhaastm nếu không nó sẽ đc vẽ bằng 1 đường thẳng nguyên thhuyr
//
//                //đường có độ dày
//                sf::RectangleShape line({150.f,50,f);
//                line.rorate(sf::degrees(45));
//
//                //đường thẳng không có độ dày
//                std::array line = {
//                    sf::Vertex{ sf::Vector2f(10.f,10.f)};
//                    sf::Vertex{ sf::Vector2f(150.f,150.f)};
//                };
//                window.draw(line.data(), line.size(), sf::Lines);
//
//        - KIỂU HÌNH DẠNG TÙY CHỈNH
//            có thể mở rộng tập hợp các lớp hình dạng với các kiểu hình dạng của riêng bạn, để làm như vậy, bạn phải bắt nguồn từ sf::Shape và ghi đè hai hàm:
//            
//            + getPointCount: trả về số điểm trong hình dạng
//            + getPoint: trả về 1 điểm của hình dạng
//
//        bạn cũng phải gọi update() được bảo về bất cứ khi nào, bất kỳ điểm nào trong hình dạng của bạn thay đổi, để lớp cơ sở đc thông báo và có thể cập nhật hình học của nó
//
//        ví dụ về class hình dạnh tủy chỉnh 
//
//            class ellipseShape : public sf::Shape
//            
//    B. THIẾT KẾ CÁC THỰC THỂ CỦA RIÊNG BẠN VỚI MẢNG ĐỈNH
//
//        - MỘT MẢNG ĐỈNH ĐƠN GIẢN
//            bây giờ cta hãy xem xét class sf::Vertex, nó chỉ đơn giản là 1 kiểu tổng hợp chứa 3 phần tử public
//                // create vertex
//                sf::Vertex vertex;
//
//                // set its position
//                vertex.position = sf::Vector2f(10.f, 50.f);
//
//                // set its color
//                vertex.color = sf:Color::Red
//
//                // set its texture coordinates
//                vertex.texCoords = sf::Vector2f(100.f,100.f);
//
//
//            hoặc sử dụng khởi tạo tổng hợp
//                
//                sf::Vertex vertex {{10.f,50.f} , sf::Color::Red,{100.f,100.f}};
//
//            bây giờ, cta hãy định nghĩa 1 pimirive(nguyên thủy). nhớ rằng 1 nguyên thủy bao gồm 1 số đỉnh, do đó cta cần 1 mảng đỉnh, sfml cung cấp 1 trình bao bọc đơn giản cho việc này sf::VertexArray.
//            nó cung cấp ngữ nghĩa của 1 mảng(tương tự như std::Vector), và cũng lưu trữ loại nguyên thủy mà các đỉnh của nó định nghĩa
//
//
//                // tạo 1 mảng có 3 đỉnh là tạo thành định nghĩa cho 1 tam giác nguyên thủy
//
//                sf::VertexArray triangle (sf::PrimitiveType::Triangles,3);
//
//                // định nghĩa tọa độ các đỉnh của tam giác đó
//                triangle[0].position = sf::Vector2f(10.f,10.f)
//                triangle[1].position = sf::Vector2f(100.f,100.f)
//                triangle[2].position = sf::Vector2f(100.f,100.f)
//
//                //define the color of the triangle's points
//                triangle[0].color = sf::Color::Red;
//                triangle[1].color = sf::Color::Green;
//                triangle[2].color = sf::Color::Blue;
//
//                // no texture coordinates here, we'll see that later
//
//        - CÁC LOẠI NGUYÊN THỦY ( PRIMITIVE)
//            bạn có thể định nghĩa các nguyên thủy 2d cơ bản nhất: điểm, đường thẳng và tam giác. ngoài ra còn có các biến thể "xích" của các loại nguyên thủy nào cho phép chia sẻ các đỉnh giữa hai nguyên thủy liên tiếp.
//        điều này có thể hữu ích vì các nguyên thủy liên tiếp thường được kết nối theo 1 cách nào đó
//                                   
//                sf::PrimitiveType::Points : một tập hợp các điểm không liên kết. các điểm này không có độ dày. chúng sẽ luôn chiếm 1 pixel duy nhất, bất kết phép biến đổi và chế độ xem hiện tại
//                sf::PrimitiveType::Lines  : một tập hợp cac đường không liên kết, các đường này không có độ dày, chugns sẽ luông rộng 1 pixel, bất kể chế độ xem và biến đổi hiện tại
//                sf::PrimitiveType::LineStrip: một tập hợp các đường thẳng được kết nối, đỉnh cuối của 1 đường thẳng được dùng làm đỉnh đầu của 1 đường thẳng tiếp theo
//                sf::PrimitiveType::TriangleStrip: một tập hợp các tam giác được kết nối, mỗi tam giác chia sẻ 2 đỉnh cuối cùng của nó với tam giác tiếp theo
//                sf::PrimitiveType::TriangleFan: một tập hợp các tam giác đc kết nối với 1 điểm trung tâm. đỉnh đầu tiên là tâm, sau đó mỗi đỉnh mới đc xác định 1 tam giác mới, sử dụng tâm và đỉnh trước đó
//                sf::PrimitiveType::Triangles: môt tập hợp các hình tam giác không liên quan
//
//
//
//*/
class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    ParticleSystem(unsigned int count) : m_particles(count), m_vertices(sf::PrimitiveType::Points, count)
    {
    }

    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
    }

    void update(sf::Time elapsed)
    {
        int tmp = 10101;
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            // update the particle lifetime
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;

            // if the particle is dead, respawn it
            if (p.lifetime <= sf::Time::Zero)
                resetParticle(i);

            // update the position of the corresponding vertex
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            m_vertices[i].color.a = static_cast<std::uint8_t>(ratio * 255);
            //m_vertices[i].color.a = ratio * ((i+i+1)^(0xffffff)>>2);
            //m_vertices[i].color.a = 

        }
    }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = nullptr;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time     lifetime;
    };

    void resetParticle(std::size_t index)
    {
        // create random number generator
        static std::random_device rd;
        static std::mt19937       rng(rd());

        // give a random velocity and lifetime to the particle
        const sf::Angle angle = sf::degrees(std::uniform_real_distribution(0.f, 360.f)(rng));
        const float     speed = std::uniform_real_distribution(50.f, 100.f)(rng);
        m_particles[index].velocity = sf::Vector2f(speed, angle);
        m_particles[index].lifetime = sf::milliseconds(std::uniform_int_distribution(1000, 3000)(rng));
        // reset the position of the corresponding vertex
        std::uniform_int_distribution<int> colorDist(0, 255);
        m_vertices[index].color = sf::Color(colorDist(rng), colorDist(rng), colorDist(rng),255);
        m_vertices[index].position = m_emitter;
    }

    std::vector<Particle> m_particles;
    sf::VertexArray       m_vertices;
    sf::Time              m_lifetime{ sf::seconds(3) };
    sf::Vector2f          m_emitter;
};
int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({ 512, 256 }), "Particles");

    // create the particle system
    ParticleSystem particles(100000);

    // create a clock to track the elapsed time
    sf::Clock clock;

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // make the particle system emitter follow the mouse
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));

        // update it
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        // draw it
        window.clear();
        window.draw(particles);
        window.display();
    }
}