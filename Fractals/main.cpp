#include <iostream>
#include <iomanip>
#include <string>
#include "julia.h"
#include "mandelbrot.h"
#include "sierpinski.h"
#include <thread>
#include <gtkmm.h>
#include <gtk/gtkgl.h>

using namespace std;

void quitClickHandler()
{
    cout<<"Quit button clicked"<<endl;
}
void juliaAnimateClickHandler()
{
    cout<<"Julia Animate button clicked"<<endl;
}
void juliaRunClickHandler()
{
    cout<<"Julia Run button clicked"<<endl;
}
void mandelAnimateClickHandler()
{
    cout<<"Mandelbrot Animate button clicked"<<endl;
}
void mandelRunClickHandler()
{
    cout<<"Mandelbrot Run button clicked"<<endl;
}

int main(int argc, char *argv[])
{

        auto app = Gtk::Application::create(argc, argv, "org.gtkmm.fractal");

        Gtk::Window window;

        window.set_default_size(1000,600);
        window.set_title("Fractal Manipulation Application");

        // Creating a Box
        Gtk::Box m_Vbox(Gtk::ORIENTATION_VERTICAL);
         window.add(m_Vbox);    // Adding virtual box to the display


        // creating an Instance of Tab menu
        Gtk::Notebook tab_menu;
        tab_menu.set_border_width(10);

        Gtk::ButtonBox m_ButtonBox;
        Gtk::Button m_Button_Quit("Exit");
        m_Button_Quit.set_margin_bottom(20);
        m_Button_Quit.signal_clicked().connect(sigc::ptr_fun(quitClickHandler));

        // Adding  Tab menu to our box
        m_Vbox.pack_start(tab_menu);
        m_Vbox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);
        m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);

        /// Julia Set Display Setup
            Gtk::Grid julia_grid;
            julia_grid.set_row_homogeneous(true);
            julia_grid.set_column_homogeneous(true);
            julia_grid.set_column_spacing(5);

            Gtk::Frame left_julia("  Change Display  ");
            left_julia.set_border_width(10);

            Gtk::Frame rigth_julia("  Control Display  ");
            rigth_julia.set_border_width(10);


            julia_grid.attach(left_julia, 0,0,1,1);
            julia_grid.attach(rigth_julia,1,0,1,1);

            /// Julia Left Panel Control Setting
                Gtk::Grid formatter;
                formatter.set_margin_top(20);
                formatter.set_row_homogeneous(true);
                formatter.set_column_homogeneous(true);
                formatter.set_row_spacing(5);

                // constant control Frame
                Gtk::Frame constant("   Constant  ");
                constant.set_margin_left(10);
                constant.set_margin_right(10);

                Gtk::Grid cGrid;         // creating a grid for formating purpose
                cGrid.set_border_width(5);
                cGrid.set_row_homogeneous(true);

                Gtk::Entry cRe, cIm;    // Creating Input box for x and Y
                cRe.set_margin_left(20);
                cIm.set_margin_left(20);
                Gtk::Label rView, iView;    // X and Y text
                rView.set_margin_left(10);
                iView.set_margin_left(10);
                rView.set_text("Real : ");
                iView.set_text("Imaginary : ");
                constant.add(cGrid);
                cGrid.attach(cRe, 1,0,1,1);
                cGrid.attach(cIm, 1,1,1,1);
                cGrid.attach(rView, 0, 0,1,1);
                cGrid.attach(iView, 0, 1,1,1);

                // Zoom control Frame
                Gtk::Frame zoom("  Zoom   ");
                zoom.set_margin_left(10);
                zoom.set_margin_right(10);
                Gtk::Scale zoomSlider;
                zoomSlider.set_range(1.0, 10.0);
                zoomSlider.set_margin_left(10);
                zoomSlider.set_margin_right(10);
                zoom.add(zoomSlider);

                // Move x and y direction Frame
                Gtk::Frame moveXY("   Move   ");
                moveXY.set_margin_left(10);
                moveXY.set_margin_right(10);

                Gtk::Grid moveGrid;         // creating a grid for formating purpose
                moveGrid.set_border_width(5);
                moveGrid.set_row_homogeneous(true);
                //moveGrid.set_column_homogeneous(true);

                Gtk::Entry moveX, moveY;    // Creating Input box for x and Y
                moveX.set_margin_left(20);
                moveY.set_margin_left(20);
                Gtk::Label xView, yView;    // X and Y text
                xView.set_margin_left(10);
                yView.set_margin_left(10);
                xView.set_text("X : ");
                yView.set_text("Y : ");
                moveXY.add(moveGrid);
                moveGrid.attach(moveX, 1,0,1,1);
                moveGrid.attach(moveY, 1,1,1,1);
                moveGrid.attach(xView, 0, 0,1,1);
                moveGrid.attach(yView, 0, 1,1,1);


                // Number of Iteration Frame
                Gtk::Frame NumIter(" Number of Iteration ");
                NumIter.set_margin_left(10);
                NumIter.set_margin_right(10);
                Gtk::Grid numIter_formatter, range_Formatter;
                numIter_formatter.set_border_width(5);
                numIter_formatter.set_row_homogeneous(true);
                range_Formatter.set_row_homogeneous(true);

                Gtk::Label number_of_iteration, Anim_range;
                number_of_iteration.set_text("Number of iteration : ");
                Anim_range.set_text("Animation : ");
                Gtk::Entry iter, A_start, A_end;
                range_Formatter.attach(A_start, 0,0,1,1);
                range_Formatter.attach(A_end, 1,0,1,1);
                A_start.set_width_chars(10);
                A_end.set_width_chars(10);

                numIter_formatter.attach(number_of_iteration, 0,0,1,1);
                numIter_formatter.attach(Anim_range, 0,1,1,1);
                numIter_formatter.attach(iter, 1,0,1,1);
                numIter_formatter.attach(range_Formatter, 1,1,1,1);

                NumIter.add(numIter_formatter);

                // Button box for holding Buttons
                Gtk::ButtonBox animAndLaunch;
                animAndLaunch.set_halign(Gtk::ALIGN_CENTER);

                Gtk::Button Anim_Button("Animate"), run_Button("Run");
                Anim_Button.set_margin_right(10);
                run_Button.set_margin_left(10);
                Anim_Button.signal_clicked().connect(sigc::ptr_fun(juliaAnimateClickHandler));
                run_Button.signal_clicked().connect(sigc::ptr_fun(juliaRunClickHandler));

                animAndLaunch.pack_start(Anim_Button, Gtk::PACK_SHRINK);
                animAndLaunch.pack_start(run_Button, Gtk::PACK_SHRINK);

            /// Packing Julia left Frame with control
                formatter.attach(constant, 0,0,1,1);
                formatter.attach(zoom,0,1,1,1);
                formatter.attach(moveXY, 0,2,1,1);
                formatter.attach(NumIter, 0,3,1,1);
                formatter.attach(animAndLaunch, 0,4,1,1);

            rigth_julia.add(formatter);

        /// Mandelbrot Set Display Setup
            Gtk::Grid mandel_grid;
            mandel_grid.set_row_homogeneous(true);
            mandel_grid.set_column_homogeneous(true);
            mandel_grid.set_column_spacing(5);

            Gtk::Frame left_mandel("  Change Display  ");
            left_mandel.set_border_width(10);

            Gtk::Frame rigth_mandel("  Control Display  ");
            rigth_mandel.set_border_width(10);


            mandel_grid.attach(left_mandel, 0,0,1,1);
            mandel_grid.attach(rigth_mandel,1,0,1,1);

            /// Mandelbrot Left Panel Control
                Gtk::Grid m_formatter;
                m_formatter.set_margin_top(20);
                m_formatter.set_row_homogeneous(true);
                m_formatter.set_column_homogeneous(true);
                m_formatter.set_row_spacing(5);

                // Zoom control Frame
                Gtk::Frame m_zoom("  Zoom   ");
                m_zoom.set_margin_left(10);
                m_zoom.set_margin_right(10);
                Gtk::Scale m_zoomSlider;
                m_zoomSlider.set_range(1.0, 10.0);
                m_zoomSlider.set_margin_left(10);
                m_zoomSlider.set_margin_right(10);
                m_zoom.add(m_zoomSlider);

                // Move x and y direction Frame
                Gtk::Frame m_moveXY("   Move   ");
                m_moveXY.set_margin_left(10);
                m_moveXY.set_margin_right(10);

                Gtk::Grid m_moveGrid;         // creating a grid for formating purpose
                m_moveGrid.set_border_width(5);
                m_moveGrid.set_row_homogeneous(true);
                //m_moveGrid.set_column_homogeneous(true);

                Gtk::Entry m_moveX, m_moveY;    // Creating Input box for x and Y
                m_moveX.set_margin_left(20);
                m_moveY.set_margin_left(20);
                Gtk::Label m_xView, m_yView;    // X and Y text
                m_xView.set_margin_left(10);
                m_yView.set_margin_left(10);
                m_xView.set_text("X : ");
                m_yView.set_text("Y : ");
                m_moveXY.add(m_moveGrid);
                m_moveGrid.attach(m_moveX, 1,0,1,1);
                m_moveGrid.attach(m_moveY, 1,1,1,1);
                m_moveGrid.attach(m_xView, 0, 0,1,1);
                m_moveGrid.attach(m_yView, 0, 1,1,1);

                // Number of Iteration Frame
                Gtk::Frame m_NumIter(" Number of Iteration ");
                m_NumIter.set_margin_left(10);
                m_NumIter.set_margin_right(10);
                Gtk::Grid m_numIter_formatter, m_range_Formatter;
                m_numIter_formatter.set_border_width(5);
                m_numIter_formatter.set_row_homogeneous(true);
                m_range_Formatter.set_row_homogeneous(true);

                Gtk::Label m_number_of_iteration, m_Anim_range;
                m_number_of_iteration.set_text("Number of iteration : ");
                m_Anim_range.set_text("Animation : ");
                Gtk::Entry m_iter, m_A_start, m_A_end;
                m_range_Formatter.attach(m_A_start, 0,0,1,1);
                m_range_Formatter.attach(m_A_end, 1,0,1,1);
                m_A_start.set_width_chars(10);
                m_A_end.set_width_chars(10);

                m_numIter_formatter.attach(m_number_of_iteration, 0,0,1,1);
                m_numIter_formatter.attach(m_Anim_range, 0,1,1,1);
                m_numIter_formatter.attach(m_iter, 1,0,1,1);
                m_numIter_formatter.attach(m_range_Formatter, 1,1,1,1);

                m_NumIter.add(m_numIter_formatter);

                // Button box for holding Buttons
                Gtk::ButtonBox m_animAndLaunch;
                m_animAndLaunch.set_halign(Gtk::ALIGN_CENTER);

                Gtk::Button m_Anim_Button("Animate"), m_run_Button("Run");
                m_Anim_Button.set_margin_right(10);
                m_run_Button.set_margin_left(10);
                m_Anim_Button.signal_clicked().connect(sigc::ptr_fun(mandelAnimateClickHandler));
                m_run_Button.signal_clicked().connect(sigc::ptr_fun(mandelRunClickHandler));

                m_animAndLaunch.pack_start(m_Anim_Button, Gtk::PACK_SHRINK);
                m_animAndLaunch.pack_start(m_run_Button, Gtk::PACK_SHRINK);

                m_formatter.attach(m_zoom, 0,0,1,1);
                m_formatter.attach(m_moveXY,0,1,1,1);
                m_formatter.attach(m_NumIter, 0,2,1,1);
                m_formatter.attach(m_animAndLaunch, 0,3,1,1);

                rigth_mandel.add(m_formatter);

        /// Sierpinski Triangle Display Setup
            Gtk::Grid Sierp_grid;
            Sierp_grid.set_row_homogeneous(true);
            Sierp_grid.set_column_homogeneous(true);
            Sierp_grid.set_column_spacing(5);

            Gtk::Frame left_Sierp("  Change Display  ");
            left_Sierp.set_border_width(10);

            Gtk::Frame rigth_Sierp("  Control Display  ");
            rigth_Sierp.set_border_width(10);


            Sierp_grid.attach(left_Sierp, 0,0,1,1);
            Sierp_grid.attach(rigth_Sierp,1,0,1,1);

            /// Sierpinski left panel control
            Gtk::Grid s_formatter;
            s_formatter.set_border_width(10);
            s_formatter.set_column_homogeneous(true);
            s_formatter.set_row_homogeneous(true);
            rigth_Sierp.add(s_formatter);

            Gtk::Frame s_numIter("  Number of Iteration    ");
            s_formatter.attach(s_numIter, 0,0,1,1);

            Gtk::Grid s_entry_formatter;
            //s_entry_formatter.set_row_homogeneous(true);
            s_entry_formatter.set_column_homogeneous(true);
            s_entry_formatter.set_border_width(5);
            s_entry_formatter.set_row_spacing(10);

            Gtk::Entry s_number_of_iteration, s_A_start, s_A_end;
            Gtk::Grid s_range_grid;
            s_range_grid.set_row_homogeneous(true);
            s_range_grid.set_column_homogeneous(true);
            s_range_grid.attach(s_A_start, 0,0,1,1);
            s_range_grid.attach(s_A_end, 1,0,1,1);
            Gtk::Label s_iter, s_Anim_range;
            s_iter.set_text("Number of iteration ");
            s_Anim_range.set_text("Animation range ");
            s_A_start.set_width_chars(5);
            s_A_end.set_width_chars(5);
            s_entry_formatter.attach(s_iter, 0,0,1,1);
            s_entry_formatter.attach(s_number_of_iteration, 1,0,1,1);
            s_entry_formatter.attach(s_Anim_range, 0,1,1,1);
            s_entry_formatter.attach(s_range_grid, 1,1,1,1);

            Gtk::ButtonBox s_buttons;
            Gtk::Button s_anim_button("Animate"), s_run_button("Run");
            s_buttons.pack_start(s_anim_button, Gtk::PACK_SHRINK);
            s_buttons.pack_start(s_run_button, Gtk::PACK_SHRINK);

            s_entry_formatter.attach(s_buttons, 1,2,1,1);
            s_numIter.add(s_entry_formatter);

        ///  Developper Team
            Gtk::Label devTeam;
            devTeam.set_line_wrap_mode(Pango::WrapMode::WRAP_WORD);
            string BAKARY = "Bakary Dounanke Diarra\t\tdounanke@gmail.com\n";
            string KHALED = "Khaled Badenjki\t\t khaled.badenjki@stud.fci-cu.edu.eg\n";
            string LEO = "Mwila Leo Mumbi\t\tmumbimwila@gmail.com";
            devTeam.set_text((BAKARY+KHALED+LEO).c_str());

        //m_Button_Quit.signal_clicked().connect(sigc::ptr_fun(on_quit_clicked));
        tab_menu.append_page(julia_grid, "  Julia Set ");
        tab_menu.append_page(mandel_grid, "  Mandelbrot Set  ");
        tab_menu.append_page(Sierp_grid, "  Sierpinski Set ");
        tab_menu.append_page(devTeam, "  Developper Team  ");

        //Gtk::Widget *glarea = get_gl
        window.show_all_children();

    return app->run(window);
}
